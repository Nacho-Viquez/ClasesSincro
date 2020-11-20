/*  Esta clase encapsula las funciones para la utilizacion de semaforos
 *  Se provee las estructuras para realizar la sincronizacion de trabajadores
 *  a traves de los metodos tradicionales Signal (V), Wait (P)
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 *
**/

#include "Condition.h"
#include <stdio.h>
#include <errno.h>


/*
 * pthread_cond_init
 */
Condition::Condition() {
	int resultado;
	resultado = pthread_cond_init(this->vc, NULL);// Reviar lo del puntero. Queda iniciado con los valores de defecto.

	if (resultado != 0){
		//Ocurrio un error
        perror("Condition constructor error: ");

		exit(1);
	}
}


/*
 * pthread_cond_destroy
 */
Condition::~Condition() {
	int resultado;

	resultado = pthread_cond_destroy(this->vc);
	if ( 0 != resultado){
		//Ocurrio un error
        perror("Condition destructor error: ");
		exit(2);
	}
}


/*
 * pthread_cond_wait
 */
int Condition::Wait( Lock * conditionLock ) {
	int resultado;

	resultado = pthread_cond_wait( this->vc, conditionLock->getLock() );
	if (0 != resultado){
		//Ocurrio un error
		perror("Condition wait error ");

		exit(3);
	}
	return resultado;
}


/*
 * pthread_cond_timedwait
 */
int Condition::TimedWait( Lock * conditionLock, long sec, long nsec ) {
   	int resultado;
   	struct timespec timeToWait;
   	timeToWait.tv_sec = sec;
   	timeToWait.tv_nsec = nsec;

   	resultado = pthread_cond_timedwait(this->vc, conditionLock->getLock(), &timeToWait);
   	if (resultado){
   		fprintf(stderr, "Conditional timed wait, failed.\n");
	    switch (resultado)
	    {
	        case ETIMEDOUT:
	            fprintf(stderr, "The time specified by abstime to pthread_cond_timedwait() has passed.\n");
	            break;
	        case EINVAL:
	            fprintf(stderr, "The value specified by abstime, cond or mutex is invalid.\n");
	            break;
	        case EPERM:
	            fprintf(stderr, "The mutex was not owned by the current thread at the time of the call.\n");
	            break;
	        default:
	            break;
	    }
   	}
   	return resultado;
}
/*
 * pthread_cond_signal
 */
int Condition::Signal() {
	int resultado;

	resultado = pthread_cond_signal(this->vc);
	if(0 != resultado){
		perror("Condition signal error ");
		exit(5);
	}
	return resultado;
}


/*
 * pthread_cond_broadcast
 */
int Condition::Broadcast() {
	int resultado;
	resultado = pthread_cond_broadcast(this->vc);
	if(0 != resultado){
		perror("Condition Broadcast error ");
		exit(6);
	}

   return resultado;
}