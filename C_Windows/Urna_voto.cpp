#include<stdio.h>
struct cdados{
	char nome[20];
	int num;
};

int menu(int *opcao);

int main()
{
	int opcao;
	FILE *arq;
	
	arq = fopen("BDurna.dat","w");
	
	
	menu(&opcao);
	
}

int menu(int *opcao)
{
printf("    _________________________________\n");
printf("   |                                 |\n");
printf("   |     Cadastrar candidato         |\n");
printf("   |  Atualizar cadadstro candidato  |\n");
printf("   |        Excluir candidado        |\n");
printf("   |              Sair               |\n");
printf("   |_________________________________|\n");
}
