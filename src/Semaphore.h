#pragma once

#include <iostream>
#include <stdexcept>
#include <sys/sem.h>

class Semaphore {
  private:
  int sem_id;

  public:
  Semaphore(std::string key, int num_semaphores, int flags = 0666);
  ~Semaphore();
  void setSemaphoreValue(int semaphore_index, int value);
  void wait(int semaphore_index);
  void signal(int semaphore_index);
};