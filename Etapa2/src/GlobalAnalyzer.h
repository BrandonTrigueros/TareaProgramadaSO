#pragma once

#include "Mailbox.h"
#include "SuperBloque.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>

class GlobalAnalyzer {
  private:
  Mailbox mailbox;
  SuperBloque superBloque;
  Semaphore canConsume;

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();
  void setMailbox(Mailbox& mailbox);
  void setSemaphore(Semaphore& canConsume);
  void recibirMensajes(u_int numMessages);
  void guardarEnDisco(std::string nombre, std::string data);
  void eliminarArchivo(std::string nombre);
  void leerArchivo(std::string nombre);
  void showDiskFiles();
  void printDisk();
};
