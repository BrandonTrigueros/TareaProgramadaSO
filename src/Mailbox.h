#pragma once

#include "common.hpp"
#include <sys/msg.h>
#include <vector>

class Mailbox {
  private:
  int queue_id;
  size_t owner_id;
  size_t queue_size;
  std::vector<size_t>* users_ids;

  Mailbox();
  ~Mailbox();

  public:
  static Mailbox& getInstance() {
    static Mailbox instance;
    return instance;
  }

  Mailbox(const Mailbox&) = delete;
  Mailbox& operator=(const Mailbox&) = delete;

  // Public member functions
  void createMsgQueue();
  void destroyMsgQueue();

  void SendMsg(Message_t* data);
  Message_t RecieveMsg();

  private:
  void AddUserPid(size_t pid);
};
