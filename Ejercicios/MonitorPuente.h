#include "../Semaforo.h"
class MonitorPuente
{
public:

	int esperando_subir, esperando_bajar, espera_maxima;
	Semaforo * sem_asendentes, *sem_desendentes, *sem_esperando_subir, *sem_esperando_bajar;


	MonitorPuente(int cantidad);
	~MonitorPuente();
	void Entrar_subiendo();
	void Salir_subiendo();
	void Entrar_bajando();
	void Salir_bajando();


};