/**
 *
 **/

#include <cstdio>
#include <cstdlib>
#include <cstring>  // strlen

#include "SSLSocket.h"

/**
 *
 **/
int main(int argc, char* argv[]) {
  SSLSocket* client;
  char userName[16] = { 0 };
  char password[16] = { 0 };
  const char* requestMessage = "\n<Body>\n\
\t<UserName>%s</UserName>\n\
\t<Password>%s</Password>\n\
</Body>\n";

  char buf[1024];
  char clientRequest[1024] = { 0 };
  int bytes;
  char *hostname, *portnum;

  client = new SSLSocket(false, nullptr, nullptr);
  if (argc != 3) {
    printf("usage: %s <hostname> <portnum>\n", argv[0]);
    exit(0);
  }
  hostname = argv[1];
  portnum = argv[2];
  client->Connect(hostname, atoi(portnum));
  printf("Enter the User Name : ");
  scanf("%s", userName);
  printf("\nEnter the Password : ");
  scanf("%s", password);
  sprintf(
      clientRequest, requestMessage, userName, password);  // construct reply
  printf("\n\nConnected with %s encryption\n", client->GetCipher());
  client->ShowCerts();  // display any certs
  client->Write(
      clientRequest, strlen(clientRequest));  // encrypt & send message
  bytes = client->Read(buf, sizeof(buf));  // get reply & decrypt
  buf[bytes] = 0;
  printf("Received: \"%s\"\n", buf);

  return 0;
}
