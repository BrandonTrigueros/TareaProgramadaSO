/**
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-ii
 *  Grupos: 2 y 3
 *
 * (versión Fedora)
 *
 **/

#ifndef VSocket_h
#define VSocket_h

#include <cstddef>

class VSocket {
  protected:
  int idSocket;
  bool IPv6;
  int port;

  public:
  void InitVSocket(char, bool = false);
  void InitVSocket(int);
  ~VSocket();

  void Close();
  int DoConnect(const char*, int);
  int DoConnect(const char*, const char*);
  virtual int Connect(const char*, int) = 0;
  virtual int Connect(const char*, const char*) = 0;

  virtual size_t Read(void*, size_t) = 0;
  virtual size_t Write(const void*, size_t) = 0;
  virtual size_t Write(const char*) = 0;

  virtual int Bind(int);
  int Listen(int);
  int DoAccept();
  virtual VSocket* Accept() = 0;
  int Shutdown(int);
};

#endif  // VSocket_h
