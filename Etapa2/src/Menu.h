#pragma once

#include "Analyzer.h"
#include "GlobalAnalyzer.h"
#include "SuperBloque.h"
#include "Mailbox.h"
#include <iostream>
#include <unistd.h>
#include <limits>

class Menu {
  private:
  Mailbox mailbox;
  SuperBloque superBloque;
  public:
  Menu(Mailbox mailbox, SuperBloque superBloque);
  ~Menu();
  void Run();
};
