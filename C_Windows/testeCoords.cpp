#include<stdio.h>
#include<conio.h>
#include<windows.h>

struct mapping{
	
	int x;
	int y;
};

int main()
{
	struct mapping coords;
	coords.x=0;
	coords.y=0;
	
	unsigned int press;
	system("color 2b");
	while( (press = getch()) != 0x1b)
	{
		press=getch();
		
		if(press==80)
		{
			coords.x+=1;
		}
			if(press==72)
			{
				coords.x-=1;
			}
				if(press==75)
				{	
					coords.y+=1;
				}
					if(press==77)
					{
						coords.y-=1;
					}
		
	//gotoxy(coords.x, coords.y);
	printf("\rx: %d    y: %d", coords.x, coords.y);
	}
	if((coords.x==5)&&(coords.y==5))
	{
		textcolor(12);
		textbackground(128);
		cprintf("\n\nCoordenadas recebidas!");
		
	}
	
}
