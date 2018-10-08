#include <conio.h>

#include <stdio.h>

int main( void )

{

unsigned char uchTecla;

//Captura até ESC seja pressionado

while( (uchTecla = getch()) != 0x1b)

printf ("\rTECLOU: %3u", uchTecla);

puts("Acabou");

return 0;

}
