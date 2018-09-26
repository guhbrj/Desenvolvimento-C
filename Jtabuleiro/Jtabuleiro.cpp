/*
1 buraco
2 volta para inicio
5 parado uma rodada
15 volta n casas(dado)

*/

#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<time.h>


//protótipo das funções
void zeraTab(int tab[], int tamanho);
void geraTab(int tabuleiro[]);
int sort();

#define TAM 70 //tamanho do tabuleiro



int main()
{
	setlocale(LC_ALL,"Portuguese");
	srand(time(NULL));
	
	int tabuleiro[TAM];
	int i;
	
	zeraTab(tabuleiro, TAM);
	geraTab(tabuleiro);
	
	
	
	for(i= 0; i< 70 ; i ++)
	{
		printf("%d ",tabuleiro[i]);
	}
}

void zeraTab(int tab[], int tamanho)
{
	//zerar tabuleiro
	
	int i;
	
	for(i=0; i<tamanho; i++)	
	{
		tab[i]=0;
	}
}

void geraTab(int tabuleiro[])
{
	int trap=1, geraTrap, contTrap=0;
	
	/*
	trap 1 - game over
	trap 2 - volta  inicio
	trap 3 - parado uma rodada
	trap 4 - volta n casas
	*/
	
	do
	{
		geraTrap=sort();
		
		if(tabuleiro[geraTrap]==0)
		{
			tabuleiro[geraTrap]=trap;
			contTrap++;
			
			switch(contTrap)
			{
				case 2: 
				trap=2;
				break;
				
				case 4:
				trap=3;
				break;
				
				case 9:	
				trap=4;
				break;
			}
		}
		
	}while(contTrap<23);
}

int sort()
{
	int random;
	
	random=1+rand()%69;
		
	
	return random;
}

