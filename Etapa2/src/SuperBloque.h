#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <utility>
#include <vector>

#include "Archivo.h"
#include "FreeSpaceManager.h"
#include "Semaphore.h"
#include "TableStructure.h"

class SuperBloque {
  private:
  char** disco;
  u_int block_size;
  u_int num_blocks;
  Semaphore mutexDisco;
  std::vector<Archivo> nameList;
  TableStructure open_files_table;
  FreeSpaceManager free_space_manager;

  public:
  SuperBloque();
  ~SuperBloque();
  void freeSuperBloque();

  int diskOpen(std::string nombre);
  void diskClose(u_int fd);
  void diskRead(u_int fd, char* buffer);
  void diskWrite(std::string texto, u_int fd);
  void diskDelete(u_int fd);

  void printDisk();
  void showDiskFiles();
  u_int getSizebyFd(u_int fd);
};
