#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
#include <string.h>
#include <windows.h>
#include <cstdlib>
//#include <conio2.h>

# define LIMPAMENS " "
#define ACIMA 72
#define ABAIXO 80
#define ENTER 13
#define ESC 27



void gotoxy( int x, int y )
{
COORD coord;
coord.X = (short)x;
coord.Y = (short)y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int MENU_PRINCIPAL()
{
int aux;
int posicao = 6, tecla;
do{
system("cls");
gotoxy(24,5);printf("____________MENU____________");
gotoxy(23,6);printf("| Cadastrar |");
gotoxy(23,7);printf("| Editar Cadastro |");
gotoxy(23,8);printf("| Listar |");
gotoxy(23,9);printf("| Deletar Cadastro |");
gotoxy(23,10);printf("| Importar BD |");
gotoxy(23,11);printf("| Exportar BD |");
gotoxy(23,12);printf("| relação |");
gotoxy(23,13);printf("| Fechar Programa |");
for(int i=24;i<52;i++)
{
gotoxy(i,14);printf("%c", 238);
}
gotoxy(24,posicao);printf("%c%c",16,16);gotoxy(50,posicao);printf("%c%c",17,17);
tecla=getch();
if(tecla == ABAIXO)
{
posicao=posicao+1;
if(posicao==14)
{
posicao=6;
}

}
if (tecla == ACIMA)
{
posicao=posicao-1;
if(posicao==5)
{
posicao=13;
}

}

}while(tecla!= ENTER);
return posicao;

}

main()
{
MENU_PRINCIPAL();
}
