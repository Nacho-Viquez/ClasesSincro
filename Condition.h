
/*  Esta clase encapsula las funciones para la utilizacion de semaforos
 *  Se provee las estructuras para realizar la sincronizacion de trabajadores
 *  a traves de los metodos tradicionales Signal (V), Wait (P)
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 *
**/

#ifndef _COND_H
#define _COND_H

#include <pthread.h>
#include "Lock.h"

class Condition {

   public:
      Condition();
      ~Condition();
      int Wait( Lock * conditionLock );
      int TimedWait( Lock * conditionLock, long = 0, long = 0 );  // Sec, uSec
      int Signal( );
      int Broadcast( );

   private:
      pthread_cond_t * vc;

};

#endif

