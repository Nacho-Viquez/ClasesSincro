#include "MonitorPuente.h"
#include <cstdio>


MonitorPuente::MonitorPuente(int cantidad){
	this->esperando_subir = 0; 
	this->esperando_bajar = 0;
	this->espera_maxima = cantidad;
	this->sem_asendentes = new Semaforo(1);
	this->sem_desendentes = new Semaforo(0); // Comienzan esperando
	this->sem_esperando_subir = new Semaforo(1);
	this->sem_esperando_bajar = new Semaforo(1);


}
MonitorPuente::~MonitorPuente(){}

void MonitorPuente::Entrar_subiendo(){
	printf("Entrar_subiendo\n");
	// metodo que se encarga de decir que un carro entra al puente de sentido acendente
	this->sem_esperando_subir->Wait();
	this->esperando_subir++;
	this->sem_esperando_subir->Signal();
	this->sem_asendentes->Wait(); // Ve a ver si puede subir  si no se queda pegado esperando que lo dejen

	this->sem_esperando_subir->Wait();
	this->esperando_subir--;
	this->sem_esperando_subir->Signal();

	this->Salir_subiendo();
}

void MonitorPuente::Salir_subiendo(){
	printf("Salir_subiendo\n");
	if (esperando_bajar >= this->espera_maxima && esperando_subir != espera_maxima){
		// dejamos pasar a los del otro lado 
		this->sem_desendentes->Signal();
	}else{
		//mandamos al siguiente nuestro
		this->sem_asendentes->Signal();
	}

}
void MonitorPuente::Entrar_bajando(){
	printf("Entrar_bajando\n");
	this->sem_esperando_bajar->Wait();

	this->esperando_bajar++; // aumentamos la cantidad de carros esperando bajar 
	this->sem_esperando_bajar->Signal();

	this->sem_desendentes->Wait(); // Revisa si tiene la posibilidad de entrar al puente
	this->sem_esperando_bajar->Wait();

	this->esperando_bajar--; // Si tiene paso el carro ya no esta esperando
	this->sem_esperando_bajar->Signal();

	this->Salir_bajando();

}
void MonitorPuente::Salir_bajando(){
	printf("Salir_bajando\n");
	if (esperando_subir >= this->espera_maxima ){
		this->sem_asendentes->Signal();
	}else{
		//podemos seguir enviando carros bajando
		this->sem_desendentes->Signal();
	}


}
