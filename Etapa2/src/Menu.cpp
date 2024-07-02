#include "Menu.h"

Menu::Menu(Mailbox mailbox, SuperBloque superBloque) {
  this->mailbox = mailbox;
  this->superBloque = superBloque;
}

Menu::~Menu() { }

void Menu::Run() {
  GlobalAnalyzer globalAnalyzer(this->mailbox, this->superBloque);
  int analyzerPID = fork();
  if (analyzerPID == 0) {
    globalAnalyzer.run();
    exit(0);
  }
  int option;
  std::string url;
  while (true) {
    std::cout << "******************************************************\n"
              << "*   BIENVENID@ A NUESTRO SISTEMA OPERATIVO SIMULADO  *\n"
              << "*                                                    *\n"
              << "*                   (\"`-/\")_.-'\"``-._                *\n"
              << "*                    . . `; -._    )-;-,_`)          *\n"
              << "*                   (v_,)'  _  )`-.\\  ``-'           *\n"
              << "*                  _.- _..-_/ / ((.'                 *\n"
              << "*                ((,.-'   ((,/                       *\n"
              << "*                                                    *\n"
              << "*  Estas son las acciones disponibles para ejecutar: *\n"
              << "*                  1 - Analizar URL                  *\n"
              << "*              2 - Ver estado del disco              *\n"
              << "*                      3 - Salir                     *\n"
              << "******************************************************\n"
              << std::endl;
    std::cin >> option;

    // Validación de entrada inválida
    if (std::cin.fail()) {
      std::cin.clear(); // Restablecer el estado de cin
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada inválida
      std::cout << "*************************************************************\n"
                << "*                                                           *\n"
                << "*   ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYba,  8b,dPPYba,  *\n"
                << "*  a8P_____88 88P'   \"Y8 88P'   \"Y8 a8\"     \"8a 88P'   \"Y8  *\n"
                << "*  8PP\"\"\"\"\"\"\" 88         88         8b       d8 88          *\n"
                << "*  \"8b,   ,aa 88         88         \"8a,   ,a8\" 88          *\n"
                << "*   `\"Ybbd8\"' 88         88          `\"YbbdP\"'  88          *\n"
                << "*                                                           *\n"
                << "*                    (Entrada invalida)                     *\n"
                << "*                                                           *\n"
                << "*************************************************************\n"
                << std::endl;
      continue; // Volver al inicio del bucle
    }

    if (option == 1) {
      std::cout << "******************************************************\n"
                << "*                                                    *\n"
                << "*     Ingrese un link o escriba \"test\" para abrir    *\n"
                << "*   el archivo /tests/url.txt como entrada de URLs.  *\n"
                << "*                                                    *\n"
                << "******************************************************\n"
                << std::endl;
      std::cin >> url;
      if (url == "test") {
        std::string file = "tests/urls.txt";
        std::ifstream filestream(file);
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
              Analyzer process;
              process.sendMessage(entrada, this->mailbox);
              exit(0);
            }
          }
        }
      } else {
        int PID = fork();
        if (PID == 0) {
          Analyzer p1;
          p1.sendMessage(url, this->mailbox);
          exit(0);
        }
      }

    } else if (option == 2) {
      std::cout << "AQUI LLEGO" << std::endl;
      this->superBloque.showDiskFiles();
      int opt;
      std::cout << "******************************************************\n"
                << "*                                                    *\n"
                << "*                  Que desea hacer?                  *\n"
                << "*                 1 - Ver un archivo                 *\n"
                << "*                    2 - Ver bloques                 *\n"
                << "*              3 - Eliminar un archivo               *\n"
                << "*                    4 - Ir atrás                    *\n"
                << "*                                                    *\n"
                << "******************************************************\n"
                << std::endl;
      std::cin >> opt;
      if (opt == 1) {
        std::string fileName;
        std::cout << "******************************************************\n"
                  << "*                                                    *\n"
                  << "*     Escriba el nombre del archivo que desea ver    *\n"
                  << "*                                                    *\n"
                  << "******************************************************\n"
                  << std::endl;
        std::cin >> fileName;
        int fileFD = this->superBloque.diskOpen(fileName);
        u_int fileSize = this->superBloque.getSizebyFd(fileFD);
        char* request = new char[fileSize];
        this->superBloque.diskRead(fileFD, request);
        std::cout << request << std::endl;
      } else if (opt == 2) {
        this->superBloque.printDisk();
      } else if (opt == 3) {
        std::string fileName;
        std::cout << "******************************************************\n"
                  << "*                                                    *\n"
                  << "*   Escriba el nombre del archvo que desea eliminar  *\n"
                  << "*                                                    *\n"
                  << "******************************************************\n"
                  << std::endl;
        std::cin >> fileName;
        u_int fileFD = this->superBloque.diskOpen(fileName);
        this->superBloque.diskDelete(fileFD);
      } else if(opt == 4) {
      } else {
        std::cout << "Opcion invalida" << std::endl;
      }
    } else if (option == 3) {
      this->mailbox.SendMsg("exit\nexit", 1);
      break;
    } else {
      std::cout
          << "*************************************************************\n"
          << "*                                                           *\n"
          << "*   ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYba,  8b,dPPYba,  *\n"
          << "*  a8P_____88 88P'   \"Y8 88P'   \"Y8 a8\"     \"8a 88P'   \"Y8  *\n"
          << "*  8PP\"\"\"\"\"\"\" 88         88         8b       d8 88          *\n"
          << "*  \"8b,   ,aa 88         88         \"8a,   ,a8\" 88          *\n"
          << "*   `\"Ybbd8\"' 88         88          `\"YbbdP\"'  88          *\n"
          << "*                                                           *\n"
          << "*                    (Entrada invalida)                     *\n"
          << "*                                                           *\n"
          << "*************************************************************\n"
          << std::endl;
    }
  }
}
