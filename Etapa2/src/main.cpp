#include "Analyzer.h"
#include "Mailbox.h"
#include "GlobalAnalyzer.h"
#include "SuperBloque.h"
#include "Menu.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

std::vector<std::string> initSource();

int main() {
  Mailbox mailbox;
  SuperBloque superBloque;
  Menu menusillo(mailbox, superBloque);
  menusillo.Run();
  /*
  if (msgctl(mailbox.queue_id, IPC_RMID, NULL) == -1) {
    perror("msgctl");
  }
  */
  return 0;
}
