#include "Analyzer.h"
#include "FreeSpaceManager.h"
#include "GlobalAnalyzer.h"
#include "Mailbox.h"
#include "Menu.h"
#include "SuperBloque.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

int main() {
  Menu menu;
  menu.run();
  return 0;
}
