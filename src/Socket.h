#ifndef Socket_h
#define Socket_h

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

class Socket {
  private:
  int idSocket;
  bool IPv6;
  int port;

  public:
  Socket(char, bool = false);
  void InitSocket(char, bool = false);

  Socket(int);
  void InitSocket(int);

  ~Socket();
  void Close();

  int Connect(const char*, int);
  int Connect(const char*, const char*);
  int Bind(int);
  int Listen(int);
  Socket* Accept();

  size_t Read(void*, size_t);
  size_t Write(const void*, size_t);
  size_t Write(const char*);

  size_t Send(const void* buffer, size_t size);
  size_t Recv(void* buffer, size_t size);

  int Shutdown(int);
};

#endif  // Socket_h
