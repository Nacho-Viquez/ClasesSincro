

/*  Esta clase encapsula las funciones para la utilizacion de semaforos
 *  Se provee las estructuras para realizar la sincronizacion de trabajadores
 *  a traves de los metodos tradicionales Signal (V), Wait (P)
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

class Lock {
   public:
      Lock();
      ~Lock();
      int Acquire();
      int Release();
      pthread_mutex_t * getLock();

   private:
      pthread_mutex_t * lock;

};

#endif


