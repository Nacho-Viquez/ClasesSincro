/*
 * Implementacion de los metodos de la clase
*/
#include "Buzon.h"
#include <cstring>


Buzon::Buzon(){
	// Se crea un Buzon mediante el llamado del metodo msgget
	this->id = msgget(KEY, 0600|IPC_CREAT);
	
	if (-1 == this->id){
		printf("Buzon::Buzon\n");
		exit(0);
	}

}

Buzon::~Buzon(){
	//Se destruye el buzon mediante la instruccion msgctl
	msgctl(this->id, IPC_RMID,(struct msqid_ds *)NULL);

}


int Buzon::Enviar(char *mensaje ){
	//Se mete un mensaje a la cola de mensajes con la instruccion msgsnd
	int resultado;
	//Mensaje
	struct msgbuf {
       long mtype;       
       char mtext[10];    
   	}msj;

   	msj.mtype = 0; // Por default revisar
	strcpy(msj.mtext,mensaje); 

	resultado = msgsnd(this->id,(struct msgbuf *)&msj, sizeof(msj.mtext), IPC_NOWAIT);
	return resultado;
}




int Buzon::Enviar(char *mensaje, int cantidad, long tipo  ){
	int resultado;

	//Declaracion de la estructura para los mensajes 
	struct msgbuf {
		long mtype;     // message type, must be > 0 
		int times;  // Times that label appears
		char label[ LABEL_SIZE ];  // Label to send to mailbox
	};

	struct msgbuf A;
	A.mtype = tipo;
	A.times = cantidad;
	strcpy(A.label,mensaje);
	//size = sizeof( A );

	resultado = msgsnd(this->id,&A, sizeof(A), IPC_NOWAIT);

	return resultado;
}


int Buzon::Recibir(void *mensaje, long tipo  ){
	//Este recibir se queda esperando a que se encuentre el mensaje.
	int resultado;
	resultado = msgrcv(this->id, mensaje,100,tipo,0);
	return resultado;

}