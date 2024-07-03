#include "Mailbox.h"
#include <iostream>

Mailbox::Mailbox() {
  queue_id = msgget(KEY_M, 0666 | IPC_CREAT);
  if (queue_id == -1) {
    perror("msgget");
  }
}

void Mailbox::destructor() {
  if (msgctl(queue_id, IPC_RMID, NULL) == -1) {
    perror("msgctl");
  }
}

void Mailbox::SendMsg(std::string etiqueta, unsigned repeticiones) {
  for (u_int i = 0; i < repeticiones; i++) {
    std::string fraccion = etiqueta.substr(i * 4000, 4000);
    Message msg;
    msg.type = getpid();
    if (i == repeticiones - 1) {
      msg.final_msg = 1;
    } else {
      msg.final_msg = 0;
    }
    strncpy(msg.mtext, fraccion.c_str(), 4000);
    msg.mtext[sizeof(msg.mtext) - 1] = '\0';
    if ((msgsnd(queue_id, &msg, sizeof(msg) - (sizeof(long)), 0) == -1)) {
      perror("msgsnd");
    }
  }
}

std::string Mailbox::RecieveMsg() {
  int pid;
  std::string etiqueta = "";
  Message msg;

  int st = msgrcv(queue_id, &msg, sizeof(msg) - (sizeof(long)), 0, 0);
  if (st == -1) {
    perror("msgrcv");
  } else {
    pid = msg.type;
    etiqueta += std::string(msg.mtext);
    if (msg.final_msg != 1) {
      while (true) {
        Message msgTemp;
        msgrcv(queue_id, &msgTemp, sizeof(msgTemp) - (sizeof(long)), pid, 0);
        etiqueta += std::string(msgTemp.mtext);
        if (msgTemp.final_msg == 1) {
          break;
        }
      }
    }
  }
  return etiqueta;
}
