#include "Analyzer.h"
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

std::vector<std::string> initSource();

int main() {
  Menu menu;
  menu.run();
  return 0;
}
