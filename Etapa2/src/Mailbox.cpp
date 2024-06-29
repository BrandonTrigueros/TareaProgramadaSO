#include "Mailbox.h"
#include <iostream>

// Constructor de la clase.
Mailbox::Mailbox() {
  // Crear el Buzón con msgget
  queue_id = msgget(KEY, 0666 | IPC_CREAT);
  if (queue_id == -1) {
    perror("msgget");
  }
}

// Destructor de la clase.
Mailbox::~Mailbox() {
  // Eliminar el buzón con msgctl
  if (msgctl(queue_id, IPC_RMID, NULL) == -1) {
    perror("msgctl");
  }
}

// Método encargado de enviar un mensaje al buzón.
void Mailbox::SendMsg(char* etiqueta, unsigned repeticiones, long mid) {
  for (u_int i = 0; i < repeticiones; i++) {
    char* fraccion = etiqueta + (i * 4040);
    Message msg;

    if (mid != 0) {
      msg.type = mid;
    } else {
      i != repeticiones - 1 ? msg.type = 1 : msg.type = 2;
    }

    msg.sender_pid = getpid();
    strncpy(msg.mtext, fraccion, 4040);
    //  msg.mtext[4039] = '\0';  // Asegurar el null-terminator
    //  Enviar el mensaje con msgsnd
    if (msgsnd(queue_id, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
      perror("msgsnd");
    }
  }
}

void Mailbox::RecieveMsg(char* etiqueta) {
  Message msg;
  int id;
  // size de etiqueta
  size_t totalLength = 0;
  // Intento recibir cualquier mensaje de tipo 1 (cuerpo)
  if (msgrcv(queue_id, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
    perror("msgrcv");
  } else {
    std::cout << "Recibí: " << msg.mtext << std::endl;
    // Si leí un mensaje, lo voy a ir rellenando
    // Copiar el mensaje recibido a la etiqueta
    etiqueta = new char[strlen(msg.mtext)];
    totalLength += strlen(msg.mtext - 1);
    strncpy(etiqueta, msg.mtext, sizeof(msg.mtext));
    id = msg.sender_pid;
    std::cout << "Procedo a buscar mensajes con el PID " << id << std::endl;
    while (true) {
      Message msgTemp;
      msgrcv(queue_id, &msgTemp, sizeof(msgTemp) - sizeof(long), 0, 0);
      std::cout << "Recibí un mensaje con el PID " << msgTemp.sender_pid
                << std::endl;
      if (msgTemp.sender_pid == id) {
        std::cout << "Encontré un mensaje más con el PID " << msgTemp.sender_pid
                  << std::endl;
        // agrego a etiqueta
        size_t lenMensaje = strlen(msgTemp.mtext);
        // Redimensionar etiqueta para acomodar el nuevo mensaje
        char* temp = (char*)realloc(etiqueta, totalLength + lenMensaje + 1);
        if (temp == NULL) {
          // Error al redimensionar la memoria
          perror("Error al redimensionar la memoria");
          free(etiqueta);
          return;
        }
        etiqueta = temp;
        // Copiar el nuevo mensaje al final de miTexto
        strcpy(etiqueta + totalLength, msgTemp.mtext);
        totalLength += lenMensaje;
        std::cout << "Mensaje de tipo " << msgTemp.type << std::endl;
        if (msgTemp.type == 2) {
          break;
        }
      } else {
        std::cout << "Rechazo mensaje con el PID distinto" << std::endl;
        SendMsg(msgTemp.mtext, 1, msgTemp.type);
      }
    }
  }
}
