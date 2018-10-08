//#include <HardwareProfile.h>
//#include <comms.h>
//#include <rfidler.h>
//#include <tamagotchi.h>
//#include <util.h>
#include<stdio.h>
// temporary? Enable debug prints for bit level decode
#define VERBOSE_TAMA_LOGGING

// tunable constants for decode
const unsigned int KBitMinPulse = 15;           // nominal bit pulse: 100 uS
const unsigned int KBitMaxPulse = 130;
const unsigned int KOneMinGap = 550;            // nominal One Gap: 600 ~ 650 uS
const unsigned int KOneMaxGap = 750;
const unsigned int KZeroMinGap = 150;           // nominal Zero Gap: 250 uS
const unsigned int KZeroMaxGap = 400;
const unsigned int KBarrierMinPulse = 200;      // nominal Barrier: 200 uS gap, 500 uS clock burst
const unsigned int KBarrierMaxPulse = 600;

const unsigned KMaxTamaMessage = 32; // max known message len from tamagotchi (for email)

// decode externally sniffed PWM
BOOL tamagotchi_decode_pwm(unsigned int pulses[], unsigned int gaps[], unsigned int count)
{
    unsigned int    index, offset, outcount;
    BOOL            decoded= FALSE;
    BYTE            out[KMaxTamaMessage];

    // FIXME skip leading pulses of zero uS - can delete when sniff_pwm() no longer gives these to us
    offset= 0;
    while ((offset < count) && (pulses[offset] == 0))
    {
        offset++;
    }

#if defined(VERBOSE_TAMA_LOGGING)
	if (offset)
    	UserMessageNum("\r\noffset past zero pulses %d", offset);
#endif

    // decode
    for(index= 0, outcount= 0; ((index + offset) < count) && (outcount < (KMaxTamaMessage - 1));)
    {
        unsigned long temp = pulses[offset + index];

        // start of byte barrier?
        if ((temp >= KBarrierMinPulse) && (temp <= KBarrierMaxPulse) && ((index + offset) < (count - 7)))
        {
            unsigned int    bits = 0;
            BYTE b = 0;

#if defined(VERBOSE_TAMA_LOGGING)
            UserMessageNum("\r\nBarrier (%d) ", temp);
#endif
            // process the byte (note changes index)
            do {
                b <<= 1;
                // peek at the next pulse to make sure it is valid
                temp = pulses[offset + index + 1];

                // bit is invalid if next pulse is wrong size
                if ((temp < KBitMinPulse) || (temp > KBitMaxPulse))
                {
                    decoded = FALSE;
                    UserMessageNum("(bad pulse count %d) ", temp);
                    break; // bad pulse width
                }

                if (index == 0)
                    decoded = TRUE;

                // value of bit depends on gap size
                temp = gaps[offset + index];
                if ((temp >= KOneMinGap) && (temp <= KOneMaxGap))
                {
                    // 1
                    b += 1;
#if defined(VERBOSE_TAMA_LOGGING)
                   UserMessageNum("1 (gap %d) ", temp);
#endif
                }
                else if ((temp >= KZeroMinGap) && (temp <= KZeroMaxGap))
                {
                    // 0
#if defined(VERBOSE_TAMA_LOGGING)
                    UserMessageNum("0 (gap %d) ", temp);
#endif
                }
                else
                {
                    decoded = FALSE;
#if defined(VERBOSE_TAMA_LOGGING)
                    UserMessageNum("(bad gap %d) ", temp);
#endif
                    break; // bad gap
                }

                ++bits;
                ++index;
            }
            while (((offset + index) < count) && (bits < 8));

            if (bits == 8)
            {
                out[outcount++] = b;
#if defined(VERBOSE_TAMA_LOGGING)
                UserMessageNum(" 0x%02x", b);
#endif
            }
        }
        else
        {
#if defined(VERBOSE_TAMA_LOGGING)
            if (index > 0)
            {
                temp = gaps[offset + index - 1];
                if ((temp >= KOneMinGap) && (temp <= KOneMaxGap))
                    UserMessageNum("\r\n1 Gap: %d, ", temp);
                else if ((temp >= KZeroMinGap) && (temp <= KZeroMaxGap))
                    UserMessageNum("\r\n0 Gap: %d, ", temp);
                else
                    UserMessageNum("\r\n??? Gap: %d, ", temp);
            }

            temp = pulses[offset + index];
            if ((temp >= KBitMinPulse) && (temp <= KBitMaxPulse))
                UserMessageNum("Bit Pulse: %d", temp);
            else if ((temp >= KBarrierMinPulse) && (temp <= KBarrierMaxPulse))
                UserMessageNum("Barrier Pulse: %d", temp);
            else
                UserMessageNum("??? Pulse: %d", temp);
#endif
            decoded = FALSE;
        }
        ++index;
    }
    
    UserMessage("%s", "\r\n");

    if (decoded)
        decoded = VerifyTamaMessage(out, outcount);

    return decoded;
}


// sum bytes (except initial sync 0xf0 and received checksum)
// and if message seems valid display hex/text dump
BOOL VerifyTamaMessage(BYTE *out, unsigned int outcount)
{
    BOOL valid = FALSE;

    // check for sync & message length bytes
    if ((outcount > 5) && (out[0] == 0xf0) && (out[2] == outcount - 4))
    {
        BYTE checksum = ChecksumTamaMessage(out, outcount - 1);

        UserMessageNum("Message checking, calculated checksum: 0x%x\r\n", checksum);
        if (checksum == out[outcount-1])
        {
            valid = TRUE;
            DumpTamaMessage(out, outcount);
        }
    }

    return valid;
}


BYTE ChecksumTamaMessage(BYTE *out, unsigned int outcount)
{
    BYTE checksum = 0;
    unsigned int    index;

    // index starts at 1 to skip sync byte
    for (index= 1; index < outcount; index++ )
        checksum += out[index];

    return checksum;
}

void DumpTamaMessage(BYTE *out, unsigned int outcount)
{
    unsigned int index;
    char         text[KMaxTamaMessage + 1];

    // print message in hex
    for (index= 0; index < outcount; index++ )
    {
        BYTE b = out[index];

        UserMessageNum(" %02X", b);
        if ((index % 8) == 7)
            UserMessage(" ", NULL);

        // convert from Tamagotchi Alphabet (eg user assigned name, email)
        text[index] = TamaAlphabetConvert(b);
    }
    text[index] = 0;

    UserMessage("    %s\r\n", text);
}


char TamaAlphabetConvert(BYTE b)
{
    if (b < 26)
        return 'A' + b;
    else if (b >= 32 && b <= 41)
        return '0' + b - 32;
    else switch (b)
    {
        case 26: return ' ';
        case 27: return '.';
        case 28: return '\'';
        case 29: return '-';
        case 30: return '!';
        // unknown
        default: return '?';
    }
}
