#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <unistd.h>
#include <utility>
#include <vector>

#include "Archivo.h"
#include "FreeSpaceManager.h"
#include "Semaphore.h"
#include "TableStructure.h"

class SuperBloque {
  private:
  char** disco;  /// Disco virtual -> Hacer memoria virutal
  u_int block_size;  /// tamaño de bloque
  u_int num_blocks;  /// cantidad de bloques
  Semaphore mutexDisco;  /// Semáforo para controlar el acceso al disco
  std::vector<Archivo*> nameList;  /// Lista de archivos en el disco
  TableStructure open_files_table;  /// Tabla de archivos abiertos
  FreeSpaceManager free_space_manager;  /// Administrador de espacio libre

  public:
  SuperBloque();
  ~SuperBloque();
  void destructor();

  // Systemcalls
  int diskOpen(std::string nombre);
  void diskClose(u_int fd);
  void diskRead(u_int fd, char* buffer);
  void diskWrite(std::string texto, u_int fd);
  void diskDelete(u_int fd);

  /// Auxiliares
  void printDisco();
  void printBloques();
  void showDiskFiles();
  u_int getSizebyFd(u_int fd);
  char** getDisco();
  Archivo* getArchivo(u_int fd);
};
