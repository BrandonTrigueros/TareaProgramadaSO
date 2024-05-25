/**
 *   UCR-ECCI
 *   CI-0123 Proyecto integrador de redes y sistemas operativos
 *
 *   SSLSocket client/server example with threads
 *
 **/

#include <cstdio>  // printf
#include <cstdlib>  // atoi
#include <cstring>  // strlen, strcmp
#include <thread>

#include "SSLSocket.h"

#define PORT 4321

void Service(SSLSocket* client) {
  char buf[1024] = { 0 };
  int sd, bytes;
  const char* ServerResponse = "\n<Body>\n\
\t<Server>os.ecci.ucr.ac.cr</Server>\n\
\t<dir>ci0123</dir>\n\
\t<Name>Proyecto Integrador Redes y sistemas Operativos</Name>\n\
\t<NickName>PIRO</NickName>\n\
\t<Description>Consolidar e integrar los conocimientos de redes y sistemas operativos</Description>\n\
\t<Author>profesores PIRO</Author>\n\
</Body>\n";
  const char* validMessage = "\n<Body>\n\
\t<UserName>piro</UserName>\n\
\t<Password>ci0123</Password>\n\
</Body>\n";

  // std::cout << "Service\n";
  // client->Accept();
  // std::cout << "Service\n";
  // client->ShowCerts();

  // bytes = client->Read(buf, sizeof(buf));
  // buf[bytes] = '\0';
  // printf("Client msg: \"%s\"\n", buf);

  // if (!strcmp(validMessage, buf)) {
  //   client->Write(ServerResponse, strlen(ServerResponse));
  // } else {
  //   client->Write("Invalid Message", strlen("Invalid Message"));
  // }

  // client->Close();

  client->SSLAccept();
  client->ShowCerts();

  bytes = client->Read(buf, sizeof(buf));
  buf[bytes] = '\0';
  printf("Client msg: \"%s\"\n", buf);

  if (!strcmp(validMessage, buf)) {
    client->Write(ServerResponse, strlen(ServerResponse));
  } else {
    client->Write("Invalid Message", strlen("Invalid Message"));
  }
  client->Close();
}

int main(int argc, char** argv) {
  SSLSocket *server, *client;
  std::thread* worker;
  int port = PORT;

  if (argc > 1) {
    port = atoi(argv[1]);
  }

  const char* certFileName = "ci0123.pem";
  const char* keyFileName = "ci0123.pem";

  server = new SSLSocket(true, certFileName, keyFileName);
  server->Bind(port);
  server->Listen(10);

  for (;;) {
    client = server->Accept();
    client->Copy(server);
    worker = new std::thread(Service, client);  // service connection
  }
}
