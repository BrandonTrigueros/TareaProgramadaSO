#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <errno.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// Constante que almacena el de carné.
#define KEY 0xC17899

// Clase encargada de informar a un proceso cuándo continuar su operación.
class Semaforo {
  public:
  Semaforo(int valorInicial = 0);
  void destructor();
  void signal();
  void wait();

  protected:
  int id;

  // Estructura requerida por el semáforo.
  union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
  };
};
#endif  // SEMAFORO_H
