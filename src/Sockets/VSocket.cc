/**
 *  Establece la definición de la clase Socket para efectuar la comunicación
 *  de procesos que no comparten memoria, utilizando un esquema de memoria
 *  distribuida.  El desarrollo de esta clase se hará en varias etapas, primero
 *  los métodos necesarios para los clientes, en la otras etapas los métodos
 *para el servidor, manejo de IP-v6, conexiones seguras y otros
 *
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-ii
 *  Grupos: 2 y 3
 *
 * (versión Fedora)
 *
 **/

#include <cstddef>
#include <cstdio>
#include <cstring>  // memset
#include <iostream>
#include <stdexcept>

#include <arpa/inet.h>  // ntohs
#include <sys/socket.h>
#include <unistd.h>  // close
// #include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>  // getaddrinfo, freeaddrinfo

#include "VSocket.h"

/**
 *  Class initializer
 *     use Unix socket system call
 *
 *  @param     char t: socket type to define
 *     's' for stream
 *     'd' for datagram
 *  @param     bool ipv6: if we need a IPv6 socket
 *
 **/
void VSocket::InitVSocket(char t, bool IPv6) {
  int st;
  int domain = (IPv6) ? AF_INET6 : AF_INET;
  int type = (t == 's') ? SOCK_STREAM : SOCK_DGRAM;
  // create with O_NONBLOCK
  st = socket(domain, type, 0);
  if (-1 == st) {
    throw std::runtime_error("VSocket::InitVSocket");
    return;
  }
  this->idSocket = st;
  this->IPv6 = IPv6;
}

/**
 *  Class initializer: Use Unix socket system call
 *
 *  @param int id: socket id
 *
 **/
void VSocket::InitVSocket(int id) {
  struct sockaddr_in address;
  socklen_t len = sizeof(address);

  if (getsockname(id, (struct sockaddr*)&address, &len) == -1) {
    throw std::runtime_error("VSocket::InitVSocket(fd)");
  } else {
    // this->port = ntohs(address.sin_port);
    this->IPv6 = (address.sin_family == AF_INET6);
    this->idSocket = id;
  }
  // this->idSocket = id;
  // this->IPv6 = false;
}

/**
 * Class destructor
 *
 **/
VSocket::~VSocket() { this->Close(); }

/**
 * Close method
 *    use Unix close system call (once opened a socket is managed like a file
 *in Unix)
 *
 **/
void VSocket::Close() {
  // if its already closed, return
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

/**
 * Connect method
 *   use "connect" Unix system call
 *
 * @param      char * host: host address in dot notation, example
 *"10.1.104.187"
 * @param      int port: process address, example 80
 *
 **/
int VSocket::DoConnect(const char* hostip, int port) {
  int st;
  struct sockaddr_in host4;
  memset((char*)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  st = inet_pton(AF_INET, hostip, &host4.sin_addr);
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

int VSocket::DoConnect(const char* hostip, const char* service) {
  // Para IPv6
  struct addrinfo hints, *res, *rp;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;  // Allow IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // Stream socket
  hints.ai_flags = 0;
  hints.ai_protocol = 0;  // Any protocol
  int st = getaddrinfo(hostip, service, &hints, &res);

  for (rp = res; rp != NULL; rp = rp->ai_next) {
    st = connect(this->idSocket, rp->ai_addr, rp->ai_addrlen);
    if (0 != st) {
      break;
    }
  }
  freeaddrinfo(res);
  return st;
}

/**
 * Bind method
 *    use "bind" Unix system call (man 3 bind) (server mode)
 *
 * @param      int port: bind a unamed socket to a port defined in sockaddr
 *structure
 *
 *  Links the calling process to a service at port
 *
 **/
int VSocket::Bind(int port) {
  int st;
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;  // IPv4
  server.sin_addr.s_addr = htonl(INADDR_ANY);  // Cualquier dirección
  server.sin_port = htons(port);  // Puerto
  int len = sizeof(server);
  ;
  if ((st = bind(this->idSocket, (struct sockaddr*)&server, len)) == -1) {
    throw std::runtime_error("VSocket::Bind");
  }
  return st;
}

/**
 * Listen method
 *
 * @param      int queue: max pending connections to enqueue (server mode)
 *
 *  This method define how many elements can wait in queue
 *
 **/
int VSocket::Listen(int queue_len) {
  int st = -1;
  st = listen(this->idSocket, queue_len);
  if (st == -1) {
    throw std::runtime_error("VSocket::Listen( int )");
  }
  return st;
}

/**
 * DoAccept method
 *    use "accept" Unix system call (man 3 accept) (server mode)
 *
 *  @returns   a new class instance
 *
 *  Waits for a new connection to service (TCP mode: stream)
 *
 **/
int VSocket::DoAccept() {
  int st = -1;
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  st = accept(this->idSocket, (struct sockaddr*)&addr, &len);
  std::cout << "Connection: " << inet_ntoa(addr.sin_addr) << ":"
            << ntohs(addr.sin_port) << std::endl;
  if (st == -1) {
    throw std::runtime_error("VSocket::DoAccept()");
  }
  return st;
}

/**
 * Shutdown method
 *    use "shutdown" Unix system call (man 3 shutdown)
 *
 *  @param	int mode define how to cease socket operation
 *
 *  Partial close the connection (TCP mode)
 *
 **/
int VSocket::Shutdown(int mode) {
  int st = -1;
  st = shutdown(this->idSocket, mode);
  if (st == -1) {
    throw std::runtime_error("VSocket::Shutdown( int )");
  }
  return st;
}

size_t VSocket::sendTo(const void* buffer, size_t size, void* addr) {
  size_t st = -1;
  socklen_t addr_len;
  this->IPv6 ? addr_len = sizeof(struct sockaddr_in6)
             : addr_len = sizeof(struct sockaddr_in);
  st = sendto(
      this->idSocket, buffer, size, 0, (struct sockaddr*)addr, addr_len);
  if (-1 == st) {
    throw std::runtime_error("VSocket::sendTo");
  } else {
    return st;
  }
}

size_t VSocket::recvFrom(void* buffer, size_t size, void* addr) {
  size_t st = -1;
  socklen_t addr_len;
  this->IPv6 ? addr_len = sizeof(struct sockaddr_in6)
             : addr_len = sizeof(struct sockaddr_in);
  st = recvfrom(
      this->idSocket, buffer, size, 0, (struct sockaddr*)addr, &addr_len);
  if (-1 == st) {
    throw std::runtime_error("VSocket::recvFrom");
  } else {
    return st;
  }
}