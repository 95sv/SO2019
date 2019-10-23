#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define PISOS 20 
#define PERSONAS 5

sem_t floors[PISOS];
sem_t controlPisos;
sem_t mutex;

typedef struct pasajero 
{
	int destino;
}* tPasajero;

typedef struct pasajero tP;

tPasajero pasajeros[PERSONAS];

int pasajerosABordo = 0;

void controlarPasajeros(int posicionActual)
{
	int j;
	for(j=0;j<PERSONAS;j++)
	{
		if(pasajeros[j]!=NULL)
		{
			if(pasajeros[j]->destino==posicionActual)
				{
					pasajeros[j]=NULL;
					pasajerosABordo--;
					printf("Pasajero %d se bajo en %d\n",j,posicionActual);
				}
		}
	}
}

void seleccionarPiso()
{
		if(pasajerosABordo < PERSONAS)
		{
			int j;
			for(j=0;j<PERSONAS;j++)
			{
				if(pasajeros[j]==NULL && rand()%2==1)
				{
					pasajeros[j]=(tPasajero)malloc(sizeof(tP));
					int dest=rand()%PISOS;
					pasajeros[j]->destino=dest;
					pasajerosABordo++;
					printf("Pasajero %d se subio a bordo con destino %d\n",j,dest);
					if(sem_trywait(&floors[dest])!=0)
						sem_post(&floors[dest]);
					else
						sem_post(&floors[dest]);
				}
			}
		}
}

void *moverAscensor(){
	while(1)
	{
		sem_wait(&controlPisos);
		sem_wait(&mutex);
		//Entro en seccion critica.
		seleccionarPiso();
		//Salgo de seccion critica.
		sem_post(&mutex);

	}
}

void *ascensor(){

	while(1){
		int indice;
		for(indice = 0; indice < PISOS ; indice++){
			sem_wait(&mutex);
			if(sem_trywait(&floors[indice]) == 0)
			{
				controlarPasajeros(indice);
				sem_post(&controlPisos);
			}
			sem_post(&mutex);
			
		}
	}
}

void inicializarPisos(){
	int i;
	for(i = 0; i<PISOS ;i++){
		if(i == 0){
			 sem_init(&floors[i],0,1);
		}
		else{
			 sem_init(&floors[i],0,0);
		}
	}
}

int main(){
	inicializarPisos();

	sem_init(&mutex,0,1);
	sem_init(&controlPisos,0,0);
	
	pthread_t ascensorHilo;
	pthread_t pisosHilos;
	
	pthread_create(&ascensorHilo,NULL,ascensor,NULL);
	pthread_create(&pisosHilos,NULL,moverAscensor,NULL);
	
	pthread_join(ascensorHilo,NULL);
	pthread_join(pisosHilos,NULL);

	sem_destroy(&mutex);
	sem_destroy(&controlPisos);

	exit(EXIT_SUCCESS);
}