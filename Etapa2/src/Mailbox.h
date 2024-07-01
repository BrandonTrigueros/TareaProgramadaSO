#pragma once

#include "Semaphore.h"
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// Constante que almacena el de carné.
#define KEY_M 0xC14653

/**
 * @brief Buzón de envío de mensajes entre procesos.
 */
class Mailbox {
  private:
  int queue_id;  /// ID de la cola de para el envío de mensajes entre procesos
  Semaphore accessQueue = Semaphore(1);
  struct Message {  /// Mensaje que se envía entre procesos
    long type;  /// Va a ser el PID
    long final_msg;  /// Indica si es el último mensaje
    char mtext[4001];  /// Etiquetas juntas
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
  void SendMsg(std::string etiqueta, unsigned repeticiones);

  /**
   * @brief Recibe un mensaje de la cola de mensajes.
   * @return El mensaje recibido.
   */
  std::string RecieveMsg();
};
