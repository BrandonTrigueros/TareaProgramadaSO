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
  std::string host, path;
  size_t pos = url.find("://");
  if (pos != std::string::npos) {
    pos += 3;
  } else {
    pos = 0;
  }
  size_t pathPos = url.find('/', pos);
  if (pathPos == std::string::npos) {
    host = url.substr(pos);
    path = "/";
  } else {
    host = url.substr(pos, pathPos - pos);
    path = url.substr(pathPos);
  }

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(host.c_str(), "80", &hints, &res) != 0) {
    perror("getaddrinfo");
    return "";
  }

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    perror("socket");
    freeaddrinfo(res);
    return "";
  }

  if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
    perror("connect");
    close(sockfd);
    freeaddrinfo(res);
    return "";
  }

  freeaddrinfo(res);

  std::string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host
      + "\r\n" + "Connection: close\r\n\r\n";

  if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
    perror("send");
    close(sockfd);
    return "";
  }

  std::string response;
  char buffer[4096];
  ssize_t bytesReceived;
  while ((bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[bytesReceived] = '\0';
    response += buffer;
  }

  if (bytesReceived < 0) {
    perror("recv");
  }

  close(sockfd);
  pos = response.find("\r\n\r\n");
  if (pos != std::string::npos) {
    response = response.substr(pos + 4);
  }
  // std::cout << response << std::endl;
  return response;
}
