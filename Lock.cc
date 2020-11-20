/*  Esta clase encapsula las funciones para la utilizacion de semaforos
 *  Se provee las estructuras para realizar la sincronizacion de trabajadores
 *  a traves de los metodos tradicionales Signal (V), Wait (P)
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 */

#include "Lock.h"


/*
 * Inicializa un candado con attr en NULL o sea los atributos por defecto son usados.
 */
Lock::Lock() {
	int resultado;
	
   this->lock = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
   resultado = pthread_mutex_init( this->lock, NULL );
   if ( 0 != resultado ) {
      perror("Error en el constructor");
      exit( resultado );
   }
}


/*
 * Destruye el candado, libera la memoria utilizada por lock
 */
Lock::~Lock() {
	int resultado;

   resultado = pthread_mutex_destroy( this->lock );
   if ( 0 != resultado ) {
      perror("Error en el destructor");

      exit( resultado );
   }

   free( this->lock );
}


/*
 * Metodo que otorga un candado.
 */
int Lock::Acquire() {
   int resultado;

   resultado = pthread_mutex_lock( this->lock );
   if ( 0 != resultado ) {
      perror("Error en el acquire");

      exit( resultado );
   }

   return resultado;
}


/*
 * Metodo que libera el candado, en otras palabras abre el candado
 */
int Lock::Release() {
	int resultado;

	resultado = pthread_mutex_unlock( this->lock );
	if ( 0 != resultado ) {
      perror("Error en el Release");

		exit( resultado );
	}

	return resultado;
}

/*
 *
 */
pthread_mutex_t * Lock::getLock() {

   return this->lock;

}
