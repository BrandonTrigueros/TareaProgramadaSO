#include "Semaphore.h"

Semaphore::Semaphore(std::string key, int num_semaphores, int flags) {
  // generamos la clave para el semáforo
  key_t key_t = ftok(key.c_str(), 'a');
  // creamos el semáforo
  sem_id = semget(key_t, num_semaphores, flags);
  if (sem_id == -1) {
    std::cout << "Error: " << errno << std::endl;
    throw std::runtime_error("Failed to create semaphore");
  }
  // inicializamos el semáforo
  if (num_semaphores == 1) {
    this->setSemaphoreValue(0, 1);
  }
}

Semaphore::~Semaphore() { }

void Semaphore::setSemaphoreValue(int semaphore_index, int value) {
  // estructura para almacenar el valor del semáforo
  union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
  } argument;
  argument.val = value;
  // establecemos el valor del semáforo
  if (semctl(sem_id, semaphore_index, SETVAL, argument) == -1) {
    throw std::runtime_error("Failed to set semaphore value");
  }
}

void Semaphore::wait(int semaphore_index) {
  struct sembuf operation;
  operation.sem_num = semaphore_index;
  operation.sem_op = -1;  // Operación de espera (decremento)
  operation.sem_flg = SEM_UNDO;
  // realizamos la operación de espera
  if (semop(sem_id, &operation, 1) == -1) {
    throw std::runtime_error("Failed to perform semaphore wait operation");
  }
}

void Semaphore::signal(int semaphore_index) {
  struct sembuf operation;
  operation.sem_num = semaphore_index;
  operation.sem_op = 1;  // Operación de señal (incremento)
  operation.sem_flg = SEM_UNDO;
  // realizamos la operación de señal
  if (semop(sem_id, &operation, 1) == -1) {
    throw std::runtime_error("Failed to perform semaphore signal operation");
  }
}
