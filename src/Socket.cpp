#include "Socket.h"

Socket::Socket(char type, bool IPv6) { this->InitSocket(type, IPv6); }
void Socket::InitSocket(char t, bool IPv6) {
  int st;
  int domain = (IPv6) ? AF_INET6 : AF_INET;
  int type = (t == 's') ? SOCK_STREAM : SOCK_DGRAM;
  st = socket(domain, type, 0);
  if (-1 == st) {
    throw std::runtime_error("VSocket::InitVSocket");
    return;
  }
  this->idSocket = st;
  this->IPv6 = IPv6;
}

Socket::Socket(int id) { this->InitSocket(id); }
void Socket::InitSocket(int id) {
  struct sockaddr_in address;
  socklen_t len = sizeof(address);
  if (getsockname(id, (struct sockaddr*)&address, &len) == -1) {
    throw std::runtime_error("VSocket::InitVSocket(fd)");
  } else {
    this->IPv6 = (address.sin_family == AF_INET6);
    this->idSocket = id;
  }
}

Socket::~Socket() { this->Close(); }
void Socket::Close() {
  if (-1 == this->idSocket) {
    throw std::runtime_error("VSocket::Close");
    return;
  }
  int st;
  st = close(this->idSocket);
  if (-1 == st) {
    throw std::runtime_error("VSocket::Close");
  }
}

int Socket::Connect(const char* host, int port) {
  int st;
  struct sockaddr_in host4;
  memset((char*)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  st = inet_pton(AF_INET, host, &host4.sin_addr);
  if (-1 == st) {
    throw(std::runtime_error("VSocket::DoConnect, inet_pton"));
  }
  host4.sin_port = htons(port);
  st = connect(idSocket, (sockaddr*)&host4, sizeof(host4));
  if (-1 == st) {
    throw(std::runtime_error("VSocket::DoConnect, connect"));
  }
  return st;
}

int Socket::Connect(const char* host, const char* service) {
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
  int st = getaddrinfo(host, service, &hints, &res);
  st = connect(this->idSocket, res->ai_addr, res->ai_addrlen);
  if (-1 == st) {
    throw std::runtime_error("VSocket::DoConnect");
  }
  freeaddrinfo(res);
  return st;
}

int Socket::Bind(int port) {
  int st;
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);
  int len = sizeof(server);
  if ((st = bind(this->idSocket, (struct sockaddr*)&server, len)) == -1) {
    throw std::runtime_error("VSocket::Bind");
  }
  return st;
}

int Socket::Listen(int queue_len) {
  int st = -1;
  st = listen(this->idSocket, queue_len);
  if (st == -1) {
    throw std::runtime_error("VSocket::Listen( int )");
  }
  return st;
}

Socket* Socket::Accept() {
  int st = -1;
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  st = accept(this->idSocket, (struct sockaddr*)&addr, &len);
  std::cout << "Connection: " << inet_ntoa(addr.sin_addr) << ":"
            << ntohs(addr.sin_port) << std::endl;
  if (st == -1) {
    throw std::runtime_error("VSocket::DoAccept()");
  }
  if (st == -1) {
    return NULL;
  } else {
    Socket* other = new Socket(st);
    return other;
  }
}

size_t Socket::Read(void* text, size_t size) {
  int st = read(this->idSocket, text, size);
  if (-1 == st) {
    throw std::runtime_error("Socket::Read( const void *, size_t )");
  }
  return st;
}

size_t Socket::Write(const void* text, size_t size) {
  ssize_t st = write(this->idSocket, text, size);
  if (-1 == st) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
  }
  return st;
}

size_t Socket::Write(const char* text) {
  int st = -1;
  st = write(this->idSocket, text, strlen(text));
  if (-1 == st) {
    throw std::runtime_error("Socket::Write( const char * )");
  }
  return st;
}

size_t Socket::Send(const void* buffer, size_t size) {
  int st = -1;
  st = send(this->idSocket, buffer, size, 0);
  if (-1 == st) {
    throw std::runtime_error("VSocket::sendTo");
  } else {
    return st;
  }
}

size_t Socket::Recv(void* buffer, size_t size) {
  int st = -1;
  st = recv(this->idSocket, buffer, size, 0);
  if (-1 == st) {
    throw std::runtime_error("VSocket::recvFrom");
  } else {
    return st;
  }
}

int Socket::Shutdown(int mode) {
  int st = -1;
  st = shutdown(this->idSocket, mode);
  if (st == -1) {
    throw std::runtime_error("VSocket::Shutdown( int )");
  }
  return st;
}