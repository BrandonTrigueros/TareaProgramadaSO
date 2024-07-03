#include "GlobalAnalyzer.h"

GlobalAnalyzer::GlobalAnalyzer() { this->superBloque = SuperBloque(); }

GlobalAnalyzer::~GlobalAnalyzer() {
  // this->superBloque.~SuperBloque();
  this->superBloque.destructor();
}

void GlobalAnalyzer::setMailbox(Mailbox& mailbox) { this->mailbox = mailbox; }

void GlobalAnalyzer::setSemaphore(Semaphore& canConsume) {
  this->canConsume = canConsume;
}

void GlobalAnalyzer::recibirMensajes(u_int numMessages) {
  for (u_int i = 0; i < numMessages; i++) {
    canConsume.wait();
    std::string message = this->mailbox.RecieveMsg();
    std::string url, etiquetas;
    std::istringstream stream(message);
    std::getline(stream, url);
    std::getline(stream, etiquetas, '\0');
    // std::cout << "URL: " << url << std::endl;
    // std::cout << "Etiquetas: " << etiquetas << std::endl;
    this->guardarEnDisco(url, etiquetas);
  }
}

void GlobalAnalyzer::guardarEnDisco(std::string nombre, std::string data) {
  int fd = this->superBloque.diskOpen(nombre);
  this->superBloque.diskWrite(data, fd);
  this->superBloque.diskClose(fd);
}

void GlobalAnalyzer::leerArchivo(std::string nombre) {
  int fd = this->superBloque.diskOpen(nombre);
  u_int size = this->superBloque.getSizebyFd(fd);
  char buffer[size];
  this->superBloque.diskRead(fd, buffer);
  std::cout << "ARCHIVO LEIDO:\n" << buffer << std::endl;
}

void GlobalAnalyzer::eliminarArchivo(std::string nombre) {
  u_int fileFD = this->superBloque.diskOpen(nombre);
  this->superBloque.diskDelete(fileFD);
}

void GlobalAnalyzer::showDiskFiles() { this->superBloque.showDiskFiles(); }

void GlobalAnalyzer::printDisk() { this->superBloque.printBloques(); }