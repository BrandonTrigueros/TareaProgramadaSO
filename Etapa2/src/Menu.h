#pragma once

#include "Analyzer.h"
#include "GlobalAnalyzer.h"
#include "Mailbox.h"
#include "SuperBloque.h"
#include <iostream>
#include <limits>
#include <sys/wait.h>
#include <unistd.h>

class Menu {

  public:
  Menu();
  ~Menu();
  void run();

  private:
  std::string menuPrincipal
      = "******************************************************\n"
        "*   BIENVENID@ A NUESTRO SISTEMA OPERATIVO SIMULADO  *\n"
        "*                                                    *\n"
        "*                   (\"`-/\")_.-'\"``-._                *\n"
        "*                    . . `; -._    )-;-,_`)          *\n"
        "*                   (v_,)'  _  )`-.\\  ``-'           *\n"
        "*                  _.- _..-_/ / ((.'                 *\n"
        "*                ((,.-'   ((,/                       *\n"
        "*                                                    *\n"
        "*  Estas son las acciones disponibles para ejecutar: *\n"
        "*                  1 - Analizar URL                  *\n"
        "*              2 - Ver estado del disco              *\n"
        "*                      3 - Salir                     *\n"
        "******************************************************\n\n";

  std::string menuError
      = "*************************************************************\n"
        "*                                                           *\n"
        "*   ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYba,  8b,dPPYba,  *\n"
        "*  a8P_____88 88P'   \"Y8 88P'   \"Y8 a8\"     \"8a 88P'   \"Y8  "
        "*\n"
        "*  8PP\"\"\"\"\"\"\" 88         88         8b       d8 88        "
        "  *\n"
        "*  \"8b,   ,aa 88         88         \"8a,   ,a8\" 88          "
        "*\n"
        "*   `\"Ybbd8\"' 88         88          `\"YbbdP\"'  88          "
        "*\n"
        "*                                                           *\n"
        "*                    (Entrada invalida)                     *\n"
        "*                                                           *\n"
        "*************************************************************\n";

  std::string pedirLink
      = "******************************************************\n"
        "*                                                    *\n"
        "*     Ingrese un link o escriba \"test\" para abrir    *\n"
        "*   el archivo /tests/url.txt como entrada de URLs.  *\n"
        "*                                                    *\n"
        "******************************************************\n";

  std::string subMenuSuperBloque
      = "******************************************************\n"
        "*                                                    *\n"
        "*                  Que desea hacer?                  *\n"
        "*                 1 - Ver un archivo                 *\n"
        "*                    2 - Ver bloques                 *\n"
        "*              3 - Eliminar un archivo               *\n"
        "*                    4 - Ir atrás                    *\n"
        "*                                                    *\n"
        "******************************************************\n";

  std::string pedirArchivo
      = "******************************************************\n"
        "*                                                    *\n"
        "*     Escriba el nombre del archivo que desea ver    *\n"
        "*                                                    *\n"
        "******************************************************\n";

  std::string archivoAEliminar
      = "******************************************************\n"
        "*                                                    *\n"
        "*   Escriba el nombre del archvo que desea eliminar  *\n"
        "*                                                    *\n"
        "******************************************************\n";
};
