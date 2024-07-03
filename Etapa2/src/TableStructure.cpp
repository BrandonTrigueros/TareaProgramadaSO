#include "TableStructure.h"

TableStructure::TableStructure() { open_files.clear(); }

TableStructure::~TableStructure() { open_files.clear(); }

void TableStructure::addEntrie(Archivo* arch) {
  open_files.insert(std::make_pair(open_files.size(), arch));
}

void TableStructure::removeEntrie(u_int index) {
  if (open_files.find(index) != open_files.end()) {
    open_files.erase(index);
  }
}

u_int TableStructure::getFD(std::string nombre) {
  for (auto it = open_files.begin(); it != open_files.end(); ++it) {
    if (it->second->nombre == nombre) {
      return it->first;
    }
  }
  return -1;
}

std::string TableStructure::isFileOpen(u_int fd) {
  if (open_files.find(fd) != open_files.end()) {
    return open_files[fd]->nombre;
  }
  return "";
}

u_int TableStructure::getSize(u_int fd) {
  if (open_files.find(fd) != open_files.end()) {
    return open_files[fd]->size;
  }
  return -1;
}