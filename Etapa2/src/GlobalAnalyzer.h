#pragma once

#include "Mailbox.h"
#include "SuperBloque.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>

class GlobalAnalyzer {
  private:
  Mailbox mailbox;
  SuperBloque superBloque;
  Semaphore canConsume;

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();
  void setMailbox(Mailbox& mailbox);
  void setSuperBloque(SuperBloque& superBloque);
  void setSemaphore(Semaphore& canConsume);
  void run();
};
