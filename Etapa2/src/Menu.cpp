#include "Menu.h"

Menu::Menu() { }

Menu::~Menu() { }

void Menu::Run() {
  int option;
  while (option != 3) {
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
    if (option == 1) {

    } else if (option == 2) {

    } else if (option == 3) {
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
