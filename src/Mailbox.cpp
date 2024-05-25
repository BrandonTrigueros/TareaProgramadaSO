#include "Mailbox.h"

Mailbox::Mailbox() {
  this->queue_id = -1;
  this->owner_id = -1;
  this->queue_size = 0;
  this->users_ids = new std::vector<size_t>();
}

void Mailbox::createMsgQueue() {
  this->queue_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0400);
  if (this->queue_id == -1) {
    std::cerr << "Error creating message queue" << std::endl;
    exit(1);
  }
}

void Mailbox::destroyMsgQueue() {
  if (msgctl(this->queue_id, IPC_RMID, NULL) == -1) {
    std::cerr << "Error destroying message queue" << std::endl;
    exit(1);
  }
}

void Mailbox::SendMsg(Message_t* data) {
  size_t ret = msgsnd(this->queue_id, data, sizeof(data), 0);
  if (ret == -1) {
    std::cerr << "Error sending message" << std::endl;
    exit(1);
  }
}

Message_t Mailbox::RecieveMsg() {
  Message_t msg;
  size_t ret = msgrcv(this->queue_id, &msg, sizeof(msg), 0, 0);
  if (ret == -1) {
    std::cerr << "Error receiving message" << std::endl;
    exit(1);
  }
  return msg;
}

Mailbox::~Mailbox() {
  this->destroyMsgQueue();
  delete this->users_ids;
}

void Mailbox::AddUserPid(size_t pid) { this->users_ids->push_back(pid); }