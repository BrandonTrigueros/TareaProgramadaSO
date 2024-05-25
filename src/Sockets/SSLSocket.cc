/**
 *  Socket class implementation
 *
 **/

#include "SSLSocket.h"

/**
 *  Class constructor: Use base class
 *
 *  @param char t: socket type to define
 *     's' for stream
 *     'd' for datagram
 *  @param bool ipv6: if we need a IPv6 socket
 *
 **/
SSLSocket::SSLSocket(bool IPv6) {
  this->InitVSocket('s', IPv6);
  this->SSLContext = nullptr;
  this->SSLStruct = nullptr;
  this->Init();
}

/**
 *  Class constructor: Use base class
 *
 *  @param char t: socket type to define
 *     's' for stream
 *     'd' for datagram
 *  @param bool IPv6: if we need a IPv6 socket
 *
 **/
SSLSocket::SSLSocket(
    bool serverContext, const char* certFileName, const char* keyFileName) {
  this->InitVSocket('s');
  this->SSLContext = nullptr;
  this->SSLStruct = nullptr;
  this->Init(serverContext, certFileName, keyFileName);
}

/**
 *  Class constructor
 *
 *  @param int id: socket descriptor
 *
 **/

SSLSocket::SSLSocket(int id) {
  this->InitVSocket(id);
  this->SSLContext = nullptr;
  this->SSLStruct = nullptr;
}

/**
 *  Class destructor
 *
 **/
SSLSocket::~SSLSocket() {
  // SSL destroy
  if (nullptr != this->SSLContext) {
    SSL_CTX_free(reinterpret_cast<SSL_CTX*>(this->SSLContext));
  }
  if (nullptr != this->SSLStruct) {
    SSL_free(reinterpret_cast<SSL*>(this->SSLStruct));
  }
  Close();
}

/**
 *  SSLInit: Use SSL_new with a defined context
 *
 *  Create a SSL object
 *
 **/
void SSLSocket::Init(
    bool serverContext, const char* certFileName, const char* keyFileName) {

  SSL* ssl;
  this->InitContext(serverContext);

  if (serverContext) {
    ssl = SSL_new((SSL_CTX*)this->SSLContext);
    if (nullptr == ssl) {
      throw std::runtime_error("SSLSocket::Init( bool )");
    }
    this->LoadCertificates(certFileName, keyFileName);
  } else {
    ssl = SSL_new((SSL_CTX*)this->SSLContext);
    if (nullptr == ssl) {
      throw std::runtime_error("SSLSocket::Init( bool )");
    }
  }
  this->SSLStruct = (void*)ssl;
}

/**
 *  InitContext: Use SSL_library_init, OpenSSL_add_all_algorithms,
 *  SSL_load_error_strings, TLS_server_method, SSL_CTX_new
 *
 *  use TLS_client_method and SSL_CTX_new
 *
 *  Creates a new SSL context to start encrypted comunications, this context is
 *  stored in class instance
 *
 *
 **/
void SSLSocket::InitContext(bool serverContext) {
  // We must initialize the library
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  // We must create a method to define our context
  const SSL_METHOD* method;
  if (serverContext) {  // If we are creating a server context
    method = TLS_server_method();
  } else {  // If we are creating a client context
    method = TLS_client_method();
  }
  // Check for errors
  if (nullptr == method) {
    throw std::runtime_error(
        "SSLSocket::InitContext( bool ) - Error getting SSL method");
  }
  SSL_CTX* context = SSL_CTX_new(method);
  // Check for errors
  if (nullptr == context) {
    ERR_print_errors_fp(stderr);
    abort();
  }
  // SSL_CTX_set_mode(context, SSL_MODE_AUTO_RETRY);
  this->SSLContext = (void*)context;
}

/**
 *  Load certificates: verify and load certificates
 *
 *  @param	const char * certFileName, file containing certificate
 *  @param	const char * keyFileName, file containing keys
 *
 **/
void SSLSocket::LoadCertificates(
    const char* certFileName, const char* keyFileName) {
  SSL_CTX* context = (SSL_CTX*)this->SSLContext;
  int st;

  if (SSL_CTX_use_certificate_file(context, certFileName, SSL_FILETYPE_PEM)
      <= 0) {  // set the local certificate from CertFile
    st = SSL_get_error((SSL*)this->SSLStruct, st);
    ERR_print_errors_fp(stderr);
    abort();
  }

  if (SSL_CTX_use_PrivateKey_file(context, keyFileName, SSL_FILETYPE_PEM)
      <= 0) {  // set the private key from KeyFile (may be the same as CertFile)
    st = SSL_get_error((SSL*)this->SSLStruct, st);
    ERR_print_errors_fp(stderr);
    abort();
  }

  if (!SSL_CTX_check_private_key(context)) {  // verify private key
    st = SSL_get_error((SSL*)this->SSLStruct, st);
    ERR_print_errors_fp(stderr);
    abort();
  }
}

/**
 *  Connect: Use SSL_connect to establish a secure conection
 *
 *  Create a SSL connection
 *
 *  @param	char * hostName, host name
 *  @param	int port, service number
 *
 **/
int SSLSocket::Connect(const char* hostName, int port) {
  int st = this->DoConnect(hostName, port);  // Establish a non ssl connection
  // Call SSL_set_fd
  st = SSL_set_fd((SSL*)this->SSLStruct, this->idSocket);
  if (0 == st) {
    throw std::runtime_error("SSLSocket::Connect( const char *, int )");
  }
  // Call SSL_connect
  st = SSL_connect((SSL*)this->SSLStruct);  // st returns -1
  // check for errors
  if (0 == st) {
    throw std::runtime_error("SSLSocket::Connect( const char *, int )");
  } else if (st < 0) {
    throw std::runtime_error("SSLSocket::Connect( const char *, int )");
  }
  return st;
}

/**
 *  Connect: Use SSL_connect to establish a secure conection
 *
 *  Create a SSL connection
 *
 *  @param	char * hostName, host name
 *  @param	char * service, service name
 *
 **/
int SSLSocket::Connect(const char* host, const char* service) {
  int st = this->DoConnect(host, service);
  // Call SSL_set_fd
  st = SSL_set_fd((SSL*)this->SSLStruct, this->idSocket);
  if (0 == st) {
    throw std::runtime_error(
        "SSLSocket::Connect( const char *, const char * )");
  }
  // Call SSL_connect
  st = SSL_connect((SSL*)this->SSLStruct);
  // check for errors
  if (0 == st) {
    SSL_get_error((SSL*)this->SSLStruct, st);
    throw std::runtime_error("SSLSocket::Connect( const char *, const char * )"
        + std::to_string(st));
  } else if (st < 0) {
    throw std::runtime_error(
        "SSLSocket::Connect( const char *, const char * ) - Fatal error");
  }
  return st;
}

/**
 *  Read: Use SSL_read to read data from an encrypted channel
 *
 *  @param	void * buffer to store data read
 *  @param	size_t size, buffer's capacity
 *
 *  @return	size_t byte quantity read
 *
 *  Reads data from secure channel
 *
 **/
size_t SSLSocket::Read(void* buffer, size_t size) {
  size_t st;
  // for (int i = 0; i < 2; ++i) {
  st = SSL_read((SSL*)this->SSLStruct, buffer, size);
  if (st <= 0) {
    throw std::runtime_error("SSLSocket::Read( void *, size_t )");
  }
  // }
  return st;
}

/**
 *  Write: Use SSL_write to write data to an encrypted channel
 *
 *  @param	void * buffer to store data read
 *  @param	size_t size, buffer's capacity
 *
 *  @return	size_t byte quantity written
 *
 *  Writes data to a secure channel
 *
 **/
size_t SSLSocket::Write(const char* string) {
  int st;
  // Use SSL_write
  st = SSL_write((SSL*)this->SSLStruct, string, strlen(string));
  if (st == 0) {
    throw std::runtime_error("SSLSocket::Write( const char * )");
  }
  return st;
}

/**
 *  Write: Use SSL_write to write data to an encrypted channel
 *
 *  @param	void * buffer to store data read
 *  @param	size_t size, buffer's capacity
 *
 *  @return	size_t byte quantity written
 *
 *  Reads data from secure channel
 *
 **/
size_t SSLSocket::Write(const void* buffer, size_t size) {
  size_t st;
  // Use SSL_read
  st = SSL_write((SSL*)this->SSLStruct, buffer, size);
  if (st <= 0) {
    int error = SSL_get_error((SSL*)this->SSLStruct, st);
    if (error == SSL_ERROR_WANT_READ || error == SSL_ERROR_WANT_WRITE) {
      return Write(buffer, size);
    } else {
      // Si hay un error, lanza una excepción
      throw std::runtime_error("SSLSocket::Read( void *, size_t )");
    }
  }
  return st;
}

/**
 * Accept method: Use base class Socket to create a new instance
 *
 *  @returns a new class instance
 *
 *  Waits for a new connection to service (TCP mode: stream)
 *
 **/
SSLSocket* SSLSocket::Accept() {
  int st = this->DoAccept();
  if (0 >= st) {
    throw std::runtime_error("SSLSocket::Accept()");
  }
  SSLSocket* ssl = new SSLSocket(st);
  return ssl;
}

/**
 * SSLAccept method: Use SSL_accept to establish a secure conection
 *
 *  Create a SSL connection
 *
 **/
SSLSocket* SSLSocket::SSLAccept() {
  int st = SSL_accept((SSL*)this->SSLStruct);
  if (0 == st) {
    throw std::runtime_error("SSLSocket::SSLAccept()");
  }
  SSLSocket* ssl = new SSLSocket(this->idSocket);
  return ssl;
}

void SSLSocket::Copy(SSLSocket* original) {
  int st;
  SSL* ssl = SSL_new((SSL_CTX*)original->SSLContext);
  if (nullptr == ssl) {
    throw std::runtime_error("SSLSocket::Copy( SSLSocket * )");
  }
  this->SSLStruct = (void*)ssl;
  this->SSLContext = original->SSLContext;
  st = SSL_set_fd(ssl, this->idSocket);
  if (0 == st) {
    throw std::runtime_error("SSLSocket::Copy( SSLSocket * )");
  }
}

/**
 *   Show SSL certificates
 *
 **/
void SSLSocket::ShowCerts() {
  X509* cert;
  char* line;

  cert = SSL_get_peer_certificate(
      (SSL*)this->SSLStruct);  // Get certificates (if available)
  if (nullptr != cert) {
    printf("Server certificates:\n");
    line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
    printf("Subject: %s\n", line);
    free(line);
    line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
    printf("Issuer: %s\n", line);
    free(line);
    X509_free(cert);
  } else {
    printf("No certificates.\n");
  }
}

/**
 *   Return the name of the currently used cipher
 *
 **/
const char* SSLSocket::GetCipher() {
  return SSL_get_cipher(reinterpret_cast<SSL*>(this->SSLStruct));
}
