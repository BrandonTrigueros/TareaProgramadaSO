#pragma once

#include "Mailbox.h"
#include "SuperBloque.h"
#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <sstream>

class GlobalAnalyzer {
  private:
  Mailbox mailbox;
  SuperBloque superBloque;

  public:
  GlobalAnalyzer();
  GlobalAnalyzer(Mailbox mailbox, SuperBloque superBloque);
  ~GlobalAnalyzer();
  void run();
};
