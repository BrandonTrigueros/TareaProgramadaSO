#pragma once

#include <limits>
#include <map>
#include <string>

#include "Archivo.h"


class TableStructure{
  public:
    std::map<u_int, Archivo> open_files;

    TableStructure() ;

    ~TableStructure() ;

    void addEntrie(Archivo arch);

    void removeEntrie(u_int index);

    u_int getFD(std::string nombre);

    std::string isFileOpen(u_int fd);

    u_int getSize(u_int fd);
};