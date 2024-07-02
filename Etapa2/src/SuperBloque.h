#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>
#include <limits>
#include <list>
#include <limits>
#include <algorithm>

#include "FreeSpaceManager.h"
#include "Semaphore.h"
#include "Archivo.h"
#include "TableStructure.h"

class SuperBloque{  
  private:
    Semaphore mutex;
    char** disco;
    u_int block_size;
    u_int num_blocks;
    std::vector<Archivo> nameList;
    TableStructure open_files_table;
    FreeSpaceManager free_space_manager;
  public:
    SuperBloque();
    void freeSuperBloque();
    ~SuperBloque();
    void showDiskFiles();
    void diskClose(u_int fd);
    int diskOpen(std::string nombre);
    void diskRead(u_int fd, char* buffer);
    void diskWrite(std::string texto, u_int fd);
    void diskDelete(u_int fd);
    u_int getSizebyFd(u_int fd);
    void printDisk();   // print freespacemanager 0 as □(U+25A1) and 1 as ■(U+25A0)
};
