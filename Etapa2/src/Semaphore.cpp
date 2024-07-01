#include "Semaphore.h"

// Método constructor de la clase.
Semaphore::Semaphore(int valorInicial) {
  // Crear un semáforo con semget y obtener el ID
  id = semget(KEY, 1, 0666 | IPC_CREAT);
  if (id == -1) {
    perror("semget");
    return;
  }

  // Inicializar el semáforo con el valor inicial usando semctl
  union semun sem_union;
  sem_union.val = valorInicial;
  if (semctl(id, 0, SETVAL, sem_union) == -1) {
    perror("semctl");
  }
}

// Método encargado de eliminar el semáforo.
void Semaphore::destructor() {
  // Eliminar el semáforo con semctl
  if (semctl(id, 0, IPC_RMID) == -1) {
    perror("semctl");
  }
}

// Método encargado de poner el semáforo en verde.
void Semaphore::signal() {
  struct sembuf sb;
  sb.sem_num = 0;  // Número del semáforo
  sb.sem_op = 1;  // Incrementar el semáforo
  sb.sem_flg = 0;  // Operación estándar

  if (semop(id, &sb, 1) == -1) {
    perror("semop signal");
  }
}

// Método encargado de esperar que el semáforo esté en verde.
void Semaphore::wait() {
  struct sembuf sb;
  sb.sem_num = 0;  // Número del semáforo
  sb.sem_op = -1;  // Decrementar el semáforo (esperar)
  sb.sem_flg = 0;  // Operación estándar

  if (semop(id, &sb, 1) == -1) {
    perror("semop wait");
  }
}
