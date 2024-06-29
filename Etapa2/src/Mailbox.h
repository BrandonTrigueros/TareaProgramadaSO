#pragma once

#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// Constante que almacena el de carné.
#define KEY 0xC14653

/**
 * @brief Buzón de envío de mensajes entre procesos.
 */
class Mailbox {
  private:
  int queue_id;  /// ID de la cola de mensajes para el envío de mensajes entre
                 /// procesos.

  struct Message {
    long type;  /// Tipos de mensajes.
    long sender_pid;  /// Process ID del emisor del mensaje.
    char mtext[4040];  /// Etiquetas juntas.
  };

  public:
  /**
   * @brief Constructor de la clase Mailbox.
   */
  Mailbox();

  /**
   * @brief Destructor de la clase Mailbox.
   */
  ~Mailbox();

  /**
   * @brief Envía un mensaje a la cola de mensajes.
   * @param data El mensaje a enviar.
   */
  void SendMsg(char* etiqueta, unsigned repeticiones, long mid = 0);

  /**
   * @brief Recibe un mensaje de la cola de mensajes.
   * @return El mensaje recibido.
   */
  void RecieveMsg(char* etiqueta);
};
