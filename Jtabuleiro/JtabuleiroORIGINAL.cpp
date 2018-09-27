/*
1 buraco
2 volta para inicio
5 parado uma rodada
15 volta n casas(dado)

*/
// implementar fila e funcoes de trap e rodada dentro de um laco de repeticao
#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>


//protótipo das funções
void zeraTab(int tab[], int tamanho);
void geraTab(int tabuleiro[]);
int sort();
int primJog(int dice, int num);
int jogaDado(int dado, struct players jogadores[], int vez);
int checkTab(struct players jogadores[], int tabuleiro[], int vez);
void exibeTab(char tabGraf[], struct players jogadores[], int vez);

#define TAM 70 //tamanho do tabuleiro

struct players{
	char nome[20];
	char ini[4];//implementar uma interface grafica com tabuleiro e iniciais dos jogadores exp: jogador gustavo - gu1
	int posicao, status, posFila;
};


int main()
{
	setlocale(LC_ALL,"Portuguese");
	srand(time(NULL));
	
	//declaração de variaveis
	int tabuleiro[TAM], num, i, dado, vez, nJogadores, volte;
	char tabGraf[TAM+1];
	
	zeraTab(tabuleiro, TAM);
	geraTab(tabuleiro);
	
	printf("Entre com o numero de jogadores: ");
	scanf("%d", &num);
	fflush(stdin);
	
struct players jogadores[num];
nJogadores = num;
//validar jogadores

for(i=0; i<num; i++)
{
	printf("Entre com o nome do jogador n# %d: ", i+1);
	gets(jogadores[i].nome);
	fflush(stdin);
	jogadores[i].status=1;
	jogadores[i].posicao=1;
	//jogadores[i].posFila=i+1;
	
}
	vez = (primJog(dado, num)-1); // verificar caso de empate
	// inicio do jogo

		printf("jogador # %d inicia a jogada", vez);
		do
	{	
	
		if(vez==num)
			{
				vez = 0;
				
			}
			
		if(jogadores[vez].status>0)
		{
		
		
			jogadores[vez].posicao+=(jogaDado(dado, jogadores, vez));
		
			switch(checkTab(jogadores, tabuleiro, vez))
			{
				
				case 0:
				printf("\njogador %d avançou para a casa %d ...",vez, jogadores[vez].posicao );	
				break;
				
				case 1:
				
				jogadores[vez].status=0;
				printf("\nQue pena jogador %d ! Você foi eliminado ...",vez );
				jogadores[vez].status=0; //game over
				nJogadores--;
				
				break;
				
				case 2:
				
				printf("Jogador %d, CHUPA! Volte para o inicio!", vez );
				jogadores[vez].posicao = 1;
				break;
				
				case 3:
					
				if(jogadores[vez].status!=2)
				{
					printf("\njogador %d ficará parado na próxima rodada!", vez );
					jogadores[vez].status=2;
				}
			
				break;
				
				case 4:
				printf("\njogador %d , que azar! Jogue o dado para voltar n casas", vez );
				//implementar
					
					 volte = 1+rand()%5;
					
					printf("... Volte %d casas...", volte);
					jogadores[vez].posicao-=volte;
					
					if(jogadores[vez].posicao<=0)
					{
						jogadores[vez].posicao=1;
					}
					
				break;
				
				default:
					printf("\n\nErro\n\n");
					break;
					
			}
			vez++;
		}
		else
		{
			vez++;
			
			
		}
		
		exibeTab(tabGraf, jogadores, vez);
		
		
		Sleep(1500);
	}while(nJogadores>1);
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
				case 1: 
				trap=2;
				
				break;
				
				case 3:
				trap=3;
				
				break;
				
				case 9:	
				
				trap=4;
				break;
			}
		}
			
	}while(contTrap<=23);
		
}

int sort()
{
	int random;
	
	random=1+rand()%69;
		
	
	return random;
}

int primJog(int dice, int num)
{
	int i, maior[2];
	
	maior[0]=0;
	maior[1]=1;
	
	for(i=1; i<=num; i++)
	{
		dice = 1+ rand()%5;
		printf("\nJogador %d jogou o dado e deu: %d\n",i ,dice);
		
		if(dice>maior[0])
		{
			maior[0] = dice;
			maior[1]= i;
		}
	}
	//printf("\n retorno da funcao primeira jogada: %d\n\n", maior[1]);
	system("PAUSE");

	return maior[1];	
}

int jogaDado(int dado, struct players jogadores[], int vez)
{
	int zero =0;
	if(jogadores[vez].status==2)
	{
		
		printf("\nJogador # %d passou a vez", vez);
		vez++;
	return zero;
	}
	else
	{
		dado = 1 + rand()%5;
//	printf("VALOR DO DADO: %d", dado); <-------------------------- sai
	return dado;
	}
}

int checkTab(struct players jogadores[], int tabuleiro[], int vez)
{
	return tabuleiro[jogadores[vez].posicao];
}

void exibeTab(char tabGraf[], struct players jogadores[], int vez)
{
	int i;
	
	for(i=0; i<=70; i++)
	{
		if(jogadores[vez].posicao==i)
		{
			tabGraf[i]=jogadores[vez].nome[0];
		}
		else
		{
			tabGraf[i]='-';
		}
		
		//printf("%c ", tabGraf[i]);
	}
}
