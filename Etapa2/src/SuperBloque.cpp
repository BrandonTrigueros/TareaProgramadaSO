#include "SuperBloque.h"

SuperBloque::SuperBloque() {
  this->block_size = 64;
  this->num_blocks = 4000;
  this->disco = new char*[this->num_blocks];
  for (u_int i = 0; i < this->num_blocks; i++) {
    this->disco[i] = new char[this->block_size];
  }
  this->mutexDisco = Semaphore(1);
}

SuperBloque::~SuperBloque() {}

void SuperBloque::freeSuperBloque() {
  for (u_int i = 0; i < this->num_blocks; i++) {
    delete[] this->disco[i];
  }
  delete this->disco;
}

int SuperBloque::diskOpen(std::string nombre) {
  //this->mutexDisco.wait();
  Archivo archivo = Archivo(nombre, "txt");
  auto it = std::find_if(nameList.begin(), nameList.end(), [&archivo](const Archivo& a) { return a == archivo; });
  if (it != nameList.end()) {
      this->open_files_table.addEntrie(archivo);
  } else {
      this->nameList.push_back(archivo);
      this->open_files_table.addEntrie(archivo);
  }
  //this->mutexDisco.signal();
  return this->open_files_table.getFD(nombre);
}

void SuperBloque::diskClose(u_int fd) {
  this->open_files_table.removeEntrie(fd);
}

void SuperBloque::diskRead(u_int fd, char* buffer) {
  //this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  u_int fileIndex;
  if (nombre == "") {
    // this->mutexDisco.signal();
    return;
  }
  for (u_int i = 0; i < this->nameList.size(); i++) {
    if (this->nameList[i].nombre == nombre) {
      fileIndex = i;
    }
  }

  for (u_int i = 0; i < this->nameList[fileIndex].indices.size(); i++) {
    strncpy(buffer + i * 64, this->disco[this->nameList[fileIndex].indices[i]], 64);
  }
  buffer[this->nameList[fileIndex].indices.size() * 64] = '\0';
  // this->mutexDisco.signal();
}

void SuperBloque::diskWrite(std::string texto, u_int fd) {
    // this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  if (nombre == "") {
    // this->mutexDisco.signal();
    return;
  }
  Archivo miArchivo(nombre, "txt");
  miArchivo.size = texto.size();
  u_int repeticiones = ceil(texto.size() / 64.0);
  for (u_int i = 0; i < repeticiones; i++) {
    u_int index = this->free_space_manager.getFreeBlock();
    this->free_space_manager.reserveBlock(index);
    miArchivo.indices.push_back(index);
    std::string fraccion = texto.substr(i * 64, 64);
    strncpy(this->disco[index], fraccion.c_str(), 64);
    this->disco[sizeof(this->disco) - 1][0] = '\0';
  }
    // this->mutexDisco.signal();
  // this->nameList.push_back(miArchivo);
}

void SuperBloque::diskDelete(u_int fd) {
  //this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  if (nombre == "") {
    //this->mutexDisco.signal();
    return;
  }
  u_int nameIndex;
  std::vector<u_int> indices;
  for (u_int i = 0; i < this->nameList.size(); i++) {
    if (nameList[i].nombre == nombre) {
      indices = nameList[i].indices;
      nameIndex = i;
    }
  }
  for (u_int i = 0; i < indices.size(); i++) {
    memset(this->disco[indices[i]], '\0', sizeof(*this->disco[indices[i]]));
    this->free_space_manager.releaseBlock(indices[i]);
  }
  this->nameList.erase(this->nameList.begin() + nameIndex);
  //this->mutexDisco.signal();
}

void SuperBloque::showDiskFiles() {
  // this->mutexDisco.wait();
  std::cout << "Archivos en disco: " << std::endl;
  for (Archivo archivo : this->nameList) {
    std::cout << archivo.nombre << std::endl;
  }
  // this->mutexDisco.signal();
}

   // print freespacemanager 0 as □(U+25A1) and 1 as ■(U+25A0)
void SuperBloque::printDisk() {
  // this->mutexDisco.wait();
  std::cout << "Disco: " << std::endl;
  for (u_int i = 0; i < this->num_blocks; i++) {
    std::cout << "[";
    for (u_int j = 0; j < this->block_size; j++) {
      if (this->disco[i][j] == '\0') {
        std::cout << "□";
      } else {
        std::cout << "■";
      }
    }
    std::cout << "]" << std::endl;
  }
  // this->mutexDisco.signal();
}

u_int SuperBloque::getSizebyFd(u_int fd) {
  return this->open_files_table.getSize(fd);
}

