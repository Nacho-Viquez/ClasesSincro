/*  Esta clase encapsula las funciones para la utilizacion de barreras
 *  Una barrera detiene una cantidad definida de hilos, una vez alcanzado
 *  ese limite, todos los hilos continuan a partir del punto de la barrera
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 *
 */

#include "Barrier.h"


/*
 *  pthread_barrier_init
 */
Barrier::Barrier() {
	int resultado;
	resultado = pthread_barrier_init(this->barrier, this->attr, this->count);
	if (resultado != 0){
		perror("Error en el constructor");
		exit(1);
	}
}


/*
 * pthread_barrier_destroy
 */
Barrier::~Barrier() {
	//Destruye la barrera apuntada por el puntero
	int resultado;
	pthread_barrier_destroy(this->barrier);
	if (resultado != 0){
		perror("Error en el destructor");
		exit(1);
	}
}


/*
 * pthread_barrier_wait
 */
void Barrier::Wait() {
	//Hace esperar a una cantidad "count" de hilos 
	pthread_barrier_wait(this->barrier); 
}

