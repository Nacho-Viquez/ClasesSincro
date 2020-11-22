#include "../Semaforo.h"
#include <stdlib.h>
#include<pthread.h>
#include <cstdio>
#include "MonitorPuente.h"

int cantidad_hilos ;
MonitorPuente * monitor;
//Semaforo * sem;

void * carro_subiendo(void * rank){
	//sem->Wait();
	monitor->Entrar_subiendo();
	//sem->Signal();
	return NULL;
}

void * carro_bajando(void * rank){
	//sem->Wait();
	monitor->Entrar_bajando();
	//sem->Signal();
	return NULL;
}

int main(int argc, char const *argv[])
{
	int N; 
	double probaCreacion;
	pthread_t * thread_handles;


	N = 3;
	cantidad_hilos = 20;
	//sem = new Semaforo(1);
	monitor = new MonitorPuente(N);

	thread_handles =(pthread_t*) malloc (cantidad_hilos*sizeof(pthread_t));

	for (int i = 0; i < cantidad_hilos; ++i)
	{
		probaCreacion =drand48();
		if (probaCreacion < 0.5){
			// Crea un carro en sentido acendente 
			pthread_create(&thread_handles[ i ],NULL,carro_subiendo,(void*)i);
			
		}else{
			// Crea un carro en sentido desendente
			pthread_create(&thread_handles[ i ],NULL,carro_bajando,(void *)i);

		}
	}
	


	for ( int thread = 0; thread < cantidad_hilos; thread++ ) { 
		pthread_join(thread_handles[thread], NULL);
	}
	printf("Todos terminaron \n");



	free( thread_handles );
	//delete(sem);
	delete(monitor);


	return 0;
}