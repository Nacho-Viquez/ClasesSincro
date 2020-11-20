

/*  Esta clase encapsula las funciones para la utilizacion de barrier
 *  Se provee las estructuras para realizar un punto de espera para los trabajadores
 *  Al crear la barrera se debe indicar cual es la cantidad de hilos que deben esperar
 *
 *  Autor: CI-0123 Proyecto integrador de redes y sistemas operativos
 *  Fecha: 2020/Ago/31
 *  Repaso: material de concurrencia
 */

#ifndef _BARRIER_H
#define _BARRIER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

class Barrier {
public:
   Barrier();
   ~Barrier();
   void Wait();

private:
   pthread_barrier_t * barrier;
   pthread_barrierattr_t * attr;
   unsigned int count;
};

#endif


