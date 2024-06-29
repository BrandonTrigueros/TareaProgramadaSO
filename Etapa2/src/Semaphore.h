#pragma once

#include <iostream>
#include <stdexcept>
#include <sys/sem.h>

/**
 * @brief Clase que representa un semáforo.
 */
class Semaphore {
  private:
  int sem_id;  /// ID del semáforo.

  public:
  /**
   * @brief Constructor de la clase Semaphore.
   * @param key La clave para generar el semáforo.
   * @param num_semaphores El número de semáforos en el conjunto.
   * @param flags Los flags para la creación del semáforo.
   */
  Semaphore(std::string key, int num_semaphores, int flags = 0666);
  /**
   * @brief Destructor de la clase Semaphore.
   */
  ~Semaphore();
  /**
   * @brief Establece el valor de un semáforo específico.
   * @param semaphore_index El índice del semáforo.
   * @param value El valor a establecer.
   */
  void setSemaphoreValue(int semaphore_index, int value);
  /**
   * @brief Realiza una operación de espera (decremento) en un semáforo
   * específico.
   * @param semaphore_index El índice del semáforo.
   */
  void wait(int semaphore_index);
  /**
   * @brief Realiza una operación de señal (incremento) en un semáforo
   * específico.
   * @param semaphore_index El índice del semáforo.
   */
  void signal(int semaphore_index);
};