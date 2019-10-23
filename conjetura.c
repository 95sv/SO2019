#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
*
*	Conjetura de Collatz
*
*/

int main(){

	int n=0;
	
	pid_t pid;

		do
		{
			printf("Ingrese un numero mayor a 1 para ejecutar la conjetura de Collatz.\n"); 
  			scanf("%d", &n);	
		}while (n < 0);

		pid = fork();

		if (pid == 0)
		{
			printf("Ejecutando hijo...\n");
			printf("%d\n",n);
			while (n!=1)
			{
				if (n%2 == 0)
				{
					n = n/2;
				}
				else if (n%2 == 1)
				{
					n = 3*(n) + 1;
				}	
			
				printf("%d\n",n);
			}
		
			printf("Finalizo hijo.\n");
		}
		else
		{
			printf("Ejecutando padre...\n");
			wait();
			printf("Finalizo padre.\n");
		}
	return 0; 
}