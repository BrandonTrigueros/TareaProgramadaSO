#include "Analyzer.h"

Analyzer::Analyzer() { }

Analyzer::~Analyzer() { }

std::map<std::string, int>* Analyzer::GetMap(std::string url) {
  return this->AnalizeHTML(this->GetHTML(url));
}

std::map<std::string, int>* Analyzer::AnalizeHTML(std::string html) {
  std::regex etiqueta_regex("<([^>]*)>");
  std::smatch coincidencias;
  std::string::const_iterator inicio = html.cbegin();
  std::string::const_iterator fin = html.cend();
  std::map<std::string, int>* etiquetas = new std::map<std::string, int>;
  while (std::regex_search(inicio, fin, coincidencias, etiqueta_regex)) {
    auto it = etiquetas->find(coincidencias[1].str());
    if (it == etiquetas->end()) {
      etiquetas->insert({ coincidencias[1].str(), 1 });
    } else {
      it->second++;
    }
    inicio = coincidencias.suffix().first;
  }
  std::map<std::string, int>::iterator it = etiquetas->begin();
  while (it != etiquetas->end()) {
    std::cout << "Etiqueta <" << it->first << "> encontrada " << it->second
              << " veces." << std::endl;
    ++it;
  }
  return etiquetas;
}

std::string Analyzer::GetHTML(std::string url) {
  Socket* socket = new Socket('s');
  socket->Connect(url.c_str(), "80");
  std::string request
      = "GET / HTTP/1.1\r\nHost: " + url + "\r\n" + "Connection: close\r\n\r\n";
  socket->Send(request.c_str(), request.length());
  char buffer[4096];
  size_t byteRecv = socket->Recv(buffer, sizeof(buffer));
  std::string response(buffer, byteRecv);
  delete socket;
  return response;
}
