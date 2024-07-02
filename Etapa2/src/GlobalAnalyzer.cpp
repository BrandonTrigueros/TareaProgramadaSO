#include "GlobalAnalyzer.h"

GlobalAnalyzer::GlobalAnalyzer(Mailbox mailbox, SuperBloque superBloque) {
  this->mailbox = mailbox;
  this->superBloque = superBloque;
}

GlobalAnalyzer::~GlobalAnalyzer() { }

void GlobalAnalyzer::run() {
  while(true) {
    std::string message = this->mailbox.RecieveMsg();
    std::string url;
    std::string etiquetas;
    std::istringstream stream(message);
    std::getline(stream, url); // Leer la primera línea que contiene el nombre
    std::getline(stream, etiquetas, '\0'); // Leer el resto del contenido como información
    if (message == "exit\nexit") {
      break;
    }

    if (url != "") {
      std::cout << "URL: " << url << std::endl;
      std::cout << "Etiquetas: " << etiquetas << std::endl;
      int fd = this->superBloque.diskOpen(url);
      this->superBloque.diskWrite(etiquetas, fd);
    }
  }
}
