#include "Buzon.h"

// Constructor de la clase.
Buzon::Buzon()
{
    // Crear el Buzón con msgget
}

// Método encargado de eliminar el buzón.
void Buzon::destructor()
{
    struct msqid_ds str;
    // Eliminar el buzón con msgctl
}

// Método encargado de enviar un mensaje al buzón.
void Buzon::enviar(char* etiqueta, unsigned repeticiones, long mid)
{
    // Inicializar el contenido del mensaje con msgbuf

	
    // Enviar el mensaje con msgsnd

}

// Método encargado de recibir un mensaje.
void Buzon::recibir(char* etiqueta, unsigned& repeticiones, int len, long mid)
{
    // Inicializar el contenido del mensaje con msgbuf


    // Recibir el mensaje con msgrcv
   

    // Sacar el mensaje del buzón. Sugerencia: strcpy
}
