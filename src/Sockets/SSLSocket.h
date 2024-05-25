/**
 *
 *   UCR-ECCI
 *   SSL Socket class interface
 *
 **/

#ifndef SSLSocket_h
#define SSLSocket_h

#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <stdexcept>

#include "VSocket.h"

class SSLSocket : public VSocket {

  private:
  // Instance variables
  void* SSLContext;  // SSL context
  void* SSLStruct;  // SSL BIO (Basic Input/Output)

  // Methods
  public:
  // Not possible to create with UDP, client constructor
  SSLSocket(bool IPv6 = false);
  SSLSocket(bool, const char*, const char*);  // For server connections
  SSLSocket(int);

  ~SSLSocket();

  int Connect(const char*, int);
  int Connect(const char*, const char*);

  size_t Read(void*, size_t);
  size_t Write(const char*);
  size_t Write(const void*, size_t);

  SSLSocket* Accept();
  SSLSocket* SSLAccept();
  void Copy(SSLSocket* original);

  void ShowCerts();
  const char* GetCipher();

  // Defaults to create a client context, true if server context needed
  void Init(bool = false, const char* certFileName = nullptr,
      const char* keyFileName = nullptr);

  private:
  void InitContext(bool);
  void LoadCertificates(const char*, const char*);
};

#endif
