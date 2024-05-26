#pragma once

#include "Semaphore.h"

#include <iostream>
#include <sys/msg.h>
#include <unistd.h>
#include <vector>

typedef struct Message {
  long type;
  char mtext[7600];  // etiquetas juntas, pow(2, 15)
  char url[256];
  int sender_pid;
} Message_t;

class Mailbox {
  private:
  int queue_id;
  size_t owner_id;
  Semaphore* canAccessQueue;
  std::vector<size_t>* users_ids;

  public:
  Mailbox();
  ~Mailbox();

  void createMsgQueue();
  void destroyMsgQueue();
  void SendMsg(Message_t data);
  Message_t RecieveMsg();

  void setOwnerId(size_t id);
  void AddUserPid(size_t pid);
};
