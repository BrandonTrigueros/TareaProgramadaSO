#pragma once

#include "Semaphore.h"

#include <iostream>
#include <sys/msg.h>
#include <unistd.h>
#include <vector>

/**
 * @brief Estructura de mensajes para su envío entre procesos.
 */
typedef struct Message {
  long type;  /// Tipos de mensajes.
  char mtext[7600];  /// etiquetas juntas(MAX 7600 chars).
  char url[256];  /// URL de página web (MAX 256 chars).
  int sender_pid;  /// Process ID del emisor del mensaje.
} Message_t;

/**
 * @brief Buzón de envío de mensajes entre procesos.
 */
class Mailbox {
  private:
  int queue_id;  /// ID de la cola de mensajes para el envío de mensajes entre
                 /// procesos.
  size_t owner_id;  /// ID del proceso
  Semaphore* canAccessQueue;  /// Semáforo para controlar el acceso a la cola de
                              /// mensajes.

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
   * @brief Crea una cola de mensajes para el buzon.
   */
  void createMsgQueue();
  /**
   * @brief Destruye la cola de mensajes del buzon.
   */
  void destroyMsgQueue();
  /**
   * @brief Envía un mensaje a la cola de mensajes.
   * @param data El mensaje a enviar.
   */
  void SendMsg(Message_t data);
  /**
   * @brief Recibe un mensaje de la cola de mensajes.
   * @return El mensaje recibido.
   */
  Message_t RecieveMsg();
  /**
   * @brief Establece el process id del dueño del buzon.
   * @param id El pid del dueño.
   */
  void setOwnerId(size_t id);
};
