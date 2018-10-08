#include<stdio.h>
#include<windows.h>
#include<time.h>
int main()
{
	char hora[6];
	FILE * arquivo;
	long long int hour;
	int horas;
	system("time /t > c:/aa.txt");
	char aux;
	arquivo = fopen("c:/aa.txt","r");
	fscanf(arquivo,"%s", hora);
	for(int i=0;i<3; i++)
	{
		if(hora[i]==':')
		{
			aux = hora[i+1];
			hora[i]=aux;
			
			
		}
		printf("\n%s", hora);
	}
	
	
	//atoi(hora,horas);
	printf("%s", hora);
hour = clock();
printf("\n%d", hour);
}

