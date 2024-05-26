#include "Analyzer.h"

Analyzer::Analyzer() { }

Analyzer::~Analyzer() { }

std::string Analyzer::getString(std::string url) {
  // Obtener el string con tags del HTML
  return this->analizeHTML(this->getHTML(url));
}

std::string Analyzer::analizeHTML(std::string html) {
  // regex para encontrar las etiquetas
  std::regex regex_tag("<([^>]*)>");
  std::smatch matches;
  std::string::const_iterator begin = html.cbegin();
  std::string::const_iterator end = html.cend();
  std::string tags;

  while (std::regex_search(begin, end, matches, regex_tag)) {
    // Añadir delimitadores de etiquetas
    tags += "<" + matches[1].str() + ">";
    begin = matches.suffix().first;
  }
  return tags;
}

std::string Analyzer::getHTML(std::string url) {
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
  // Crear socket
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    perror("socket");
    freeaddrinfo(res);
    return "";
  }
  // Conectar
  if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
    perror("connect");
    close(sockfd);
    freeaddrinfo(res);
    return "";
  }
  freeaddrinfo(res);
  std::string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host
      + "\r\n" + "Connection: close\r\n\r\n";
  // Enviar petición
  if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
    perror("send");
    close(sockfd);
    return "";
  }
  std::string response;
  char buffer[4096];
  ssize_t bytesReceived;
  // Recibir respuesta
  while ((bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[bytesReceived] = '\0';
    response += buffer;
  }
  if (bytesReceived < 0) {
    perror("recv");
  }
  // Cerrar socket
  close(sockfd);
  pos = response.find("\r\n\r\n");
  if (pos != std::string::npos) {
    response = response.substr(pos + 4);
  }
  return response;
}

void Analyzer::sendMessage(std::string url, Mailbox* mailbox) {
  Message_t message;
  // Asignar valores al mensaje
  message.type = 1;
  message.sender_pid = getpid();
  std::strcpy(message.url, url.c_str());
  // Obtenemos el string con las etiquetas
  std::strcpy(message.mtext, getString(url).c_str());
  // std::cout << message.mtext << std::endl;
  std::cout << "Trying to send from child number: " << message.sender_pid
            << std::endl;
  mailbox->SendMsg(message);
}