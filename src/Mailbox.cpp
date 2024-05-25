#include "Mailbox.h"

Mailbox::Mailbox() {
  this->queue_id = -1;
  this->owner_id = -1;
  this->semaphore = new Semaphore("C17899", 1, IPC_CREAT | 0666);
  this->users_ids = new std::vector<size_t>();
}

Mailbox::~Mailbox() {
  this->destroyMsgQueue();
  delete this->users_ids;
  delete this->semaphore;
}

Mailbox& Mailbox::getInstance() {
  static Mailbox instance;
  return instance;
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
  this->semaphore->wait(0);
  if (msgsnd(this->queue_id, data, sizeof(data), 0) == -1) {
    std::cerr << "Error sending message" << std::endl;
    exit(1);
  }
  this->semaphore->signal(0);
}

Message_t Mailbox::RecieveMsg() {
  this->semaphore->wait(0);
  Message_t msg;
  if (msgrcv(this->queue_id, &msg, sizeof(msg), 0, 0) == -1) {
    std::cerr << "Error receiving message" << std::endl;
    exit(1);
  }
  this->semaphore->signal(0);
  return msg;
}

void Mailbox::setOwnerId(size_t id) { this->owner_id = id; }
void Mailbox::AddUserPid(size_t pid) { this->users_ids->push_back(pid); }
