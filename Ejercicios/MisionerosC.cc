#include "../Semaforo.h"
#include <stdlib.h>
#include<pthread.h>
#include <cstdio>

int thread_count ;

int  cantidadMisioneros , cantidadCanivales;
Semaforo  *semMisioneros, *semCanibales, *semCruzar;

void cruzar (){
	semCruzar->Wait();
	if (cantidadMisioneros >= 2 && cantidadCanivales < 2 ){
		if (cantidadCanivales == 1) {
			// se envia 1 canibal y 2 misioneros
			cantidadMisioneros = cantidadMisioneros - 2;
			cantidadCanivales = cantidadCanivales -1; 
			printf("Dos misioneros y un canibal\n");
		}else{
			// se envian todos misioneros 
			cantidadMisioneros  = cantidadMisioneros -3;
			printf("Todos son misionerossss !\n");
		}
	}

	semCruzar->Signal();
}


void *llegaM (void * rank){
	// Metodo que se encarga de llevar a cabo el manejo de los misioneros
	//Semaforo *sem = (Semaforo*) rank;
	printf("Hola soy misionero \n");
	semMisioneros->Wait();
	cantidadMisioneros++;
	printf("Estoy en el semaforoooo\n");
	semMisioneros->Signal();
	cruzar();
	return NULL;

}

void *llegaC(void * rank){
	//metodo que se encarva de llevar a cabo el manejo de los canibales
	printf("hola soy canibal\n");
	semCanibales->Wait();
	cantidadCanivales++;
	semCanibales->Signal();

	cruzar();
	return NULL;
	
}


int main(int argc, char const *argv[])
{
	
	double probaCreacion ;
	long thread ; 
	pthread_t * thread_handles;

	cantidadCanivales = 0;
	cantidadMisioneros = 0;
	semCanibales = new Semaforo(1);
	semMisioneros = new Semaforo(1);
	semCruzar = new Semaforo(1);

	cantidadMisioneros = 0;
	cantidadCanivales = 0;
	thread_count = 10;
	thread_handles =(pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
	printf("Despues de la declaracion\n");

	for (int i = 0; i < 10; ++i)
	{
		probaCreacion =drand48();
		if (probaCreacion < 0.5){
			// Crea un misionero
			pthread_create(&thread_handles[ i ],NULL,llegaM,(void*)i);
			
		}else{
			//Crea un canibal
			pthread_create(&thread_handles[ i ],NULL,llegaC,(void *)i);

		}
	}
	


	for ( int thread = 0; thread < thread_count; thread++ ) { 
		pthread_join(thread_handles[thread], NULL);
	}
	printf("Todos terminaron \n");



	free( thread_handles );
	//delete(semMisioneros);
	//delete(semCanibales);
	//delete(semCruzar);
	printf(" %d\n", cantidadCanivales);
	printf("%d\n", cantidadMisioneros);

	return 0;
}