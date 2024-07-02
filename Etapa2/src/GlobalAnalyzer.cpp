#include "GlobalAnalyzer.h"

GlobalAnalyzer::GlobalAnalyzer() { }

GlobalAnalyzer::~GlobalAnalyzer() { }

void GlobalAnalyzer::setMailbox(Mailbox& mailbox) { this->mailbox = mailbox; }

void GlobalAnalyzer::setSuperBloque(SuperBloque& superBloque) {
  this->superBloque = superBloque;
}

void GlobalAnalyzer::setSemaphore(Semaphore& canConsume) {
  this->canConsume = canConsume;
}

void GlobalAnalyzer::run() {
  while (true) {
    canConsume.wait();
    std::string message = this->mailbox.RecieveMsg();
    if (message != "exit\nexit") {
      std::string url, etiquetas;
      std::istringstream stream(message);
      std::getline(stream, url);
      std::getline(stream, etiquetas, '\0');
      if (url != "") {
        std::cout << "URL: " << url << std::endl;
        std::cout << "Etiquetas: " << etiquetas << std::endl;
        // int fd = this->superBloque.diskOpen(url);
        // this->superBloque.diskWrite(etiquetas, fd);
      }
    } else {
      break;
    }
  }
}
