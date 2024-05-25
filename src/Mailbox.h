#pragma once

#include "Semaphore.h"

#include <iostream>
#include <sys/msg.h>
#include <vector>

typedef struct Message {
  void* data;
  size_t sender_pid;
} Message_t;

class Mailbox {
  private:
  int queue_id;
  size_t owner_id;
  Semaphore* semaphore;
  std::vector<size_t>* users_ids;

  Mailbox();
  ~Mailbox();

  public:
  static Mailbox& getInstance();

  Mailbox(const Mailbox&) = delete;
  Mailbox& operator=(const Mailbox&) = delete;

  void createMsgQueue();
  void destroyMsgQueue();
  void SendMsg(Message_t* data);
  Message_t RecieveMsg();

  void setOwnerId(size_t id);
  void AddUserPid(size_t pid);
};
