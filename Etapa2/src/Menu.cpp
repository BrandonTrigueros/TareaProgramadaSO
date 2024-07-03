#include "Menu.h"

Menu::Menu() { }

Menu::~Menu() { }

void Menu::run() {
  Mailbox mailbox;
  Semaphore canConsume(0);
  GlobalAnalyzer globalAnalyzer;
  globalAnalyzer.setMailbox(mailbox);
  globalAnalyzer.setSemaphore(canConsume);

  int option;
  std::string url;
  while (true) {
    std::cout << this->menuPrincipal << std::endl;
    std::cin >> option;
    // Atajo entradas invalidas no ints
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
          std::vector<std::string> vectorEntrada;
          std::string entrada;
          while (std::getline(buffer, entrada, '\n')) {
            vectorEntrada.push_back(entrada);
          }
          for (u_int i = 0; i < vectorEntrada.size(); i++) {
            int PID = fork();
            if (PID == 0) {
              Analyzer analyzer;
              analyzer.sendMessage(vectorEntrada[i], mailbox);
              canConsume.signal();
              exit(0);
            }
          }
          globalAnalyzer.recibirMensajes(vectorEntrada.size());
        }
      } else {
        int PID = fork();
        if (PID == 0) {
          Analyzer p1;
          p1.sendMessage(url, mailbox);
          canConsume.signal();
          exit(0);
        }
        globalAnalyzer.recibirMensajes(1);
      }

    } else if (option == 2) {

      globalAnalyzer.showDiskFiles();
      int opt;
      std::cout << this->subMenuSuperBloque << std::endl;
      std::cin >> opt;

      if (opt == 1) {
        std::string fileName;
        std::cout << this->pedirArchivo << std::endl;
        std::cin >> fileName;
        globalAnalyzer.leerArchivo(fileName);
      } else if (opt == 2) {
        globalAnalyzer.printDisk();
      } else if (opt == 3) {
        std::string fileName;
        std::cout << this->archivoAEliminar << std::endl;
        std::cin >> fileName;
        globalAnalyzer.eliminarArchivo(fileName);
      } else if (opt == 4) {
      } else {
        std::cout << "Opcion invalida" << std::endl;
      }

    } else if (option == 3) {
      mailbox.SendMsg("exit\nexit", 1);
      canConsume.signal();
      canConsume.destructor();
      mailbox.destructor();
      break;
    } else {
      std::cout << menuError << std::endl;
    }
  }
}
