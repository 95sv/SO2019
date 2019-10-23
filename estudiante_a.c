#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t A;
sem_t B;
sem_t C;
sem_t D;
sem_t E;


void * func_A()
{
	while(1)
		if(sem_trywait(&A)!=0)
			printf("El estudiante A finalizo sus estudios.\n");
}

void * func_B()
{
	while(1)
		if(sem_trywait(&B)!=0)
			printf("El estudiante B finalizo sus estudios.\n");
}

void * func_C()
{
	while(1)
		if(sem_trywait(&C)!=0)
			printf("El estudiante C finalizo sus estudios.\n");
}

void * func_D()
{
	while(1)
		if(sem_trywait(&D)!=0)
			printf("El estudiante D finalizo sus estudios.\n");
}

void * func_E()
{
	while(1)
		if(sem_trywait(&E)!=0)
			printf("El estudiante E finalizo sus estudios.\n");
}

int main()
{
	pthread_cond_t request = PTHREAD_COND_INITIALIZER;//Para probar
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//Para probar
	
	
	sem_init(&A,0,3);
	sem_init(&B,0,5);
	sem_init(&C,0,2);
	sem_init(&D,0,3);
	sem_init(&E,0,4);
	
	pthread_t estudiante_A;
	pthread_t estudiante_B;
	pthread_t estudiante_C;
	pthread_t estudiante_D;
	pthread_t estudiante_E;
	
	pthread_create(&estudiante_A,NULL,func_A,NULL);
	pthread_create(&estudiante_B,NULL,func_B,NULL);
	pthread_create(&estudiante_C,NULL,func_C,NULL);
	pthread_create(&estudiante_D,NULL,func_D,NULL);
	pthread_create(&estudiante_E,NULL,func_E,NULL);
	
	/*
	*
	*	Intento para inicializar todo al mismo tiempo
	*	
	*	Retora valor para saber error de tipo int	
	*
	*	Retora valor para saber error de tipo int
	*	
	*/
	
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&request, &mutex); 
	
	pthread_join(estudiante_A,NULL);
	pthread_join(estudiante_B,NULL);
	pthread_join(estudiante_C,NULL);
	pthread_join(estudiante_D,NULL);
	pthread_join(estudiante_E,NULL);
	
	pthread_mutex_unlock(&mutex);//Para probar

	exit(0);
}