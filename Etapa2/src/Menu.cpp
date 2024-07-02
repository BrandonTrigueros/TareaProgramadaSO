#include "Menu.h"

Menu::Menu() { }

Menu::~Menu() { }

void Menu::run() {
  Mailbox mailbox;
  SuperBloque superBloque;
  Semaphore canConsume(0);

  GlobalAnalyzer globalAnalyzer;
  globalAnalyzer.setMailbox(mailbox);
  globalAnalyzer.setSuperBloque(superBloque);
  globalAnalyzer.setSemaphore(canConsume);

  int pid = fork();
  if (pid == 0) {
    globalAnalyzer.run();
    exit(0);
  }

  int option;
  std::string url;
  while (true) {
    std::cout << this->menuPrincipal << std::endl;
    std::cin >> option;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << this->menuError << std::endl;
      continue;
    }
    if (option == 1) {
      std::cout << this->pedirLink << std::endl;
      std::cin >> url;

      if (url == "test") {
        std::ifstream filestream("tests/urls.txt");
        if (!filestream.is_open()) {
          std::cerr << "Error al abrir el archivo " << std::endl;
        } else {
          std::stringstream buffer;
          buffer << filestream.rdbuf();
          filestream.close();
          std::string entrada;
          while (std::getline(buffer, entrada, '\n')) {
            int PID = fork();
            if (PID == 0) {
              Analyzer analyzer;
              analyzer.sendMessage(entrada, mailbox);
              canConsume.signal();
              exit(0);
            }
          }
        }
      } else {
        int PID = fork();
        if (PID == 0) {
          Analyzer p1;
          p1.sendMessage(url, mailbox);
          canConsume.signal();
          exit(0);
        }
      }

      // } else if (option == 2) {
      //   superBloque.showDiskFiles();
      //   int opt;
      //   std::cout << this->subMenuSuperBloque << std::endl;
      //   std::cin >> opt;

      //   if (opt == 1) {
      //     std::string fileName;
      //     std::cout << this->pedirArchivo << std::endl;
      //     std::cin >> fileName;
      //     int fileFD = superBloque.diskOpen(fileName);
      //     u_int fileSize = superBloque.getSizebyFd(fileFD);
      //     char* request = new char[fileSize];
      //     superBloque.diskRead(fileFD, request);
      //     std::cout << request << std::endl;
      //   } else if (opt == 2) {
      //     superBloque.printDisk();
      //   } else if (opt == 3) {
      //     std::string fileName;
      //     std::cout << this->archivoAEliminar << std::endl;
      //     std::cin >> fileName;
      //     u_int fileFD = superBloque.diskOpen(fileName);
      //     superBloque.diskDelete(fileFD);
      //   } else if (opt == 4) {
      //   } else {
      //     std::cout << "Opcion invalida" << std::endl;
      //   }

    } else if (option == 3) {
      mailbox.SendMsg("exit\nexit", 1);
      canConsume.signal();
      break;
    } else {
      std::cout << menuError << std::endl;
    }
  }
}
