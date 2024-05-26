#include "GlobalAnalyzer.h"

GlobalAnalyzer::GlobalAnalyzer() {
  this->mailbox = new Mailbox();
  this->mailbox->setOwnerId(getpid());
  this->urls = new std::vector<std::string>;
  this->url_maps = new std::map<std::string, std::map<std::string, int>>;
}

GlobalAnalyzer::~GlobalAnalyzer() {
  delete this->urls;
  delete this->url_maps;
  delete this->mailbox;
}

void GlobalAnalyzer::createProcesses(std::vector<std::string>* urls) {
  this->urls = urls;
  // Por cada URL se crea un proceso hijo
  for (size_t i = 0; i < urls->size(); i++) {
    pid_t pid = fork();
    if (pid == -1) {
      std::cout << "Error creating child process" << std::endl;
      return;
      // Si soy un proceso hijo, envío un mensaje con las etiquetas
    } else if (pid == 0) {
      Analyzer analyzer;
      analyzer.sendMessage(urls->at(i), this->mailbox);
      exit(0);
    } else {
      std::cout << "Child created with PID: " << pid << std::endl;
    }
  }
}

void GlobalAnalyzer::readMailbox() {
  // Mientras la cantidad de mapas obtenidos no sea la misma cantidad de URLs
  // obtenidos, se intenta sacar mensajes de la cola
  while (this->url_maps->size() < this->urls->size()) {
    Message_t message = this->mailbox->RecieveMsg();
    if (message.sender_pid != -1) {
      std::string tags(message.mtext);
      std::cout << "Message recieved from child number: " << message.sender_pid
                << std::endl;
      std::map<std::string, int> tags_map = analyzeTags(tags);
      this->url_maps->insert({ message.url, tags_map });
    }
  }

  for (auto it = this->url_maps->begin(); it != this->url_maps->end(); it++) {
    std::cout << "Tags per URL:" << std::endl;
    std::cout << it->first << ":" << std::endl;
    for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
      std::cout << "<" << it2->first << ">" << ": " << it2->second << std::endl;
    }
  }
}

std::map<std::string, int> GlobalAnalyzer::analyzeTags(std::string tags) {
  std::map<std::string, int> contador;
  std::istringstream ss(tags);
  std::string etiqueta;
  // Recorre el string de etiquetas
  while (std::getline(ss, etiqueta, '<')) {
    // Ignora el texto antes de la etiqueta
    size_t pos = etiqueta.find('>');
    if (pos != std::string::npos) {
      etiqueta = etiqueta.substr(0, pos);
      // Si la etiqueta no está vacía, actualiza el contador
      if (!etiqueta.empty()) {
        contador[etiqueta]++;
      }
    }
  }
  return contador;
}
