#include "SuperBloque.h"

SuperBloque::SuperBloque() {
  this->block_size = 64;
  this->num_blocks = 4000;
  this->disco = new char*[this->num_blocks];
  for (u_int i = 0; i < this->num_blocks; i++) {
    this->disco[i] = new char[this->block_size];
    memset(this->disco[i], '\0', sizeof(*this->disco[i]));
  }
  this->mutexDisco = Semaphore(1);
}

SuperBloque::~SuperBloque() { }

void SuperBloque::destructor() {
  for (u_int i = 0; i < this->num_blocks; i++) {
    delete[] this->disco[i];
  }
  delete[] this->disco;
}

int SuperBloque::diskOpen(std::string nombre) {
  // this->mutexDisco.wait();
  Archivo* archivo = nullptr;
  u_int nameListSize = this->nameList.size();
  // std::cout << "list size: " << nameListSize << std::endl;
  for (u_int i = 0; i < nameListSize; i++) {
    if (this->nameList[i]->nombre == nombre) {
      archivo = this->nameList[i];
      // std::cout << "Superbloque: Archivo " << nombre << " existe en disco"
      //           << std::endl;
      // std::cout << "nombre de archivo existente: " << archivo->nombre
      //           << std::endl;
      this->open_files_table.addEntrie(archivo);
    }
  }
  if (archivo == nullptr) {
    // std::cout << "Superbloque: Archivo " << nombre
    //           << " no existe en disco... Creando archivo" << std::endl;
    archivo = new Archivo(nombre, "txt");
    this->nameList.push_back(archivo);
    this->open_files_table.addEntrie(archivo);
  }
  // this->mutexDisco.signal();
  return this->open_files_table.getFD(archivo->nombre);
}

void SuperBloque::diskClose(u_int fd) {
  this->open_files_table.removeEntrie(fd);
}

void SuperBloque::diskRead(u_int fd, char* buffer) {
  // this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  if (nombre == "") {
    // this->mutexDisco.signal();
    return;
  }
  Archivo* miArchivo = this->open_files_table.open_files[fd];
  for (u_int i = 0; i < miArchivo->indices.size(); i++) {
    strncpy(buffer + i * 64, this->disco[miArchivo->indices[i]], 64);
  }
  buffer[miArchivo->size] = '\0';
  // this->mutexDisco.signal();
}

void SuperBloque::diskWrite(std::string texto, u_int fd) {
  // this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  if (nombre == "") {
    // this->mutexDisco.signal();
    // std::cout << "Archivo no en tabla de archivos abiertos" << std::endl;
    return;
  }
  // std::cout << "Archivo en tabla de archivos abiertos " << nombre <<
  // std::endl;
  Archivo* miArchivo = this->open_files_table.open_files[fd];
  // std::cout << "Archivo registrado como " << miArchivo->nombre << std::endl;
  miArchivo->size += texto.size();
  // std::cout << "Escribiendo: " << texto << " con tamaño: " << texto.size()
  //           << std::endl;
  u_int repeticiones = ceil(texto.size() / 64.0);
  // std::cout << "Este archivo requiere " << repeticiones << " bloques"
  //           << std::endl;
  for (u_int i = 0; i < repeticiones; i++) {
    u_int index = this->free_space_manager.getFreeBlock();
    this->free_space_manager.reserveBlock(index);
    miArchivo->indices.push_back(index);
    std::string fraccion = texto.substr(i * 64, 64);
    // std::cout << "Escribiendo en bloque " << index
    //           << " la fracción: " << fraccion << std::endl;
    strncpy(this->disco[index], fraccion.c_str(), 64);
    if (fraccion.size() < 64) {
      this->disco[index][fraccion.size()] = '\0';
    }
  }
  // this->mutexDisco.signal();
}

void SuperBloque::diskDelete(u_int fd) {
  // this->mutexDisco.wait();
  std::string nombre = this->open_files_table.isFileOpen(fd);
  if (nombre == "") {
    // this->mutexDisco.signal();
    return;
  }
  Archivo* miArchivo = this->getArchivo(fd);
  for (u_int i = 0; i < miArchivo->indices.size(); i++) {
    this->free_space_manager.releaseBlock(miArchivo->indices[i]);
    memset(this->disco[miArchivo->indices[i]], '\0', 64);
  }
  this->open_files_table.removeEntrie(fd);
  for (u_int i = 0; i < this->nameList.size(); i++) {
    if (this->nameList[i]->nombre == nombre) {
      this->nameList.erase(this->nameList.begin() + i);
    }
  }
  delete miArchivo;
}

void SuperBloque::showDiskFiles() {
  // this->mutexDisco.wait();
  std::cout << "Archivos en disco: " << std::endl;
  for (Archivo* archivo : this->nameList) {
    std::cout << archivo->nombre << std::endl;
  }
  // this->mutexDisco.signal();
}

void SuperBloque::printDisco() {
  // this->mutexDisco.wait();
  std::cout << "Disco: " << std::endl;
  for (u_int i = 0; i < this->num_blocks; i++) {
    std::cout << "[ ";
    for (u_int j = 0; j < this->block_size; j++) {
      if (this->disco[i][j] == '\0') {
        std::cout << "□";
      } else {
        std::cout << "■";
      }
    }
    std::cout << " ]" << std::endl;
  }
  // this->mutexDisco.signal();
}

// print freespacemanager 0 as □(U+25A1) and 1 as ■(U+25A0)
void SuperBloque::printBloques() {
  // this->mutexDisco.wait();
  this->free_space_manager.print();
  // this->mutexDisco.signal();
}

u_int SuperBloque::getSizebyFd(u_int fd) {
  return this->open_files_table.getSize(fd);
}

Archivo* SuperBloque::getArchivo(u_int fd) {
  return this->open_files_table.open_files[fd];
}

char** SuperBloque::getDisco() { return this->disco; }