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

// int main() {
// Menu menu;
// GlobalAnalyzer globalAnalyzer;
// globalAnalyzer.guardarEnDisco("test.txt", menu.menuPrincipal);
// globalAnalyzer.leerArchivo("test.txt");

// int PID = fork();
// if (PID == 0) {
//   globalAnalyzer.guardarEnDisco("test.txt", "Hola Mundo");
// }

// u_int size = superBloque.getSizebyFd(fd);
// std::cout << "Size: " << size << std::endl;
// char buffer[size];
// superBloque.diskRead(fd, buffer);
// std::cout << buffer << std::endl;
// }
