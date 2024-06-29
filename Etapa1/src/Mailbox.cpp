#include "Mailbox.h"

Mailbox::Mailbox() {
  this->queue_id = -1;
  this->owner_id = -1;
  this->canAccessQueue = new Semaphore("C17899", 1, IPC_CREAT | 0666);
  this->users_ids = new std::vector<size_t>();
  this->createMsgQueue();
}

Mailbox::~Mailbox() {
  this->destroyMsgQueue();
  delete this->users_ids;
  delete this->canAccessQueue;
}

void Mailbox::createMsgQueue() {
  // Creo una cola para envío de mensajes entre procesos
  this->queue_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0666);
  if (this->queue_id == -1) {
    std::cerr << "Error creating message queue " << getpid() << std::endl;
    exit(1);
  }
}

void Mailbox::destroyMsgQueue() {
  if (msgctl(this->queue_id, IPC_RMID, NULL) == -1) {
    std::cerr << "Error destroying message queue " << getpid() << std::endl;
    exit(1);
  }
}

void Mailbox::SendMsg(Message_t data) {
  // Semáforo que limita el acceso a la cola
  this->canAccessQueue->wait(0);
  // Envía el mensaje
  if (msgsnd(this->queue_id, &data, sizeof(Message_t) - sizeof(long), 0)
      == -1) {
    std::cerr << errno << std::endl;
    std::cerr << "Error sending message " << getpid() << std::endl;
    exit(1);
  }
  this->canAccessQueue->signal(0);
}

Message_t Mailbox::RecieveMsg() {
  this->canAccessQueue->wait(0);
  struct msqid_ds buf;
  // Revisa si la cola está vacía
  if (msgctl(this->queue_id, IPC_STAT, &buf) == -1) {
    std::cerr << "Error getting message queue status " << getpid() << std::endl;
    exit(1);
  }
  Message_t msg;
  if (buf.msg_qnum != 0) {
    // De haber elementos en la cola, recibe un mensaje
    if (msgrcv(this->queue_id, &msg, sizeof(Message_t) - sizeof(long), 1, 0)
        == -1) {
      std::cout << errno << std::endl;
      std::cerr << "Error receiving message " << getpid() << std::endl;
      exit(1);
    }
  } else {
    msg.sender_pid = -1;
    msg.mtext[0] = '\0';
  }
  this->canAccessQueue->signal(0);
  return msg;
}

void Mailbox::setOwnerId(size_t id) { this->owner_id = id; }
void Mailbox::AddUserPid(size_t pid) { this->users_ids->push_back(pid); }
