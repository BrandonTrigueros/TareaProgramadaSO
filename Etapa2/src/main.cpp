#include "Analyzer.h"
#include "Mailbox.h"
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
  int PID = fork();
  if (PID == 0) {
    Analyzer p1;
    p1.sendMessage("https://os.ecci.ucr.ac.cr/ci0123/", mailbox);
    exit(0);
  } else {
    std::string etiquetas = mailbox.RecieveMsg();
    std::cout << etiquetas << std::endl;
  }
  /*
  std::vector<std::string> urls = initSource();
  if (urls.empty()) {
    return 1;
  } else {
    crear storage xd :v hailGrasa
    creo buzon
    creo global-Anal
    pego el anal global con el disco
    pego buzon con el anal global
    run a toa la vara
    while siempre {
      despliego menú
      if (nuevo url) {
        fork(nuevo url)
      } else if (eleminar data de url) {
        analGlobal(eliminar data del disco)
      } else if (q se sabe) {
        analGlobal(imprimo disco)
      }
    }
  }
  */
  return 0;
}

// Recepción de URLs
std::vector<std::string> initSource() {
  int input;
  std::vector<std::string> urls;
  std::cout << "¿Desea introducir los URLs manualmente?\n1 para sí, 2 para no"
            << std::endl;
  std::cin >> input;
  if (input == 1) {
    std::cout << "Introduzca un URL para analizar su HTML" << std::endl;
    while (true) {
      std::string url;
      std::cout
          << "Introduzca un URL o escriba \"exit\" si no desea agregar más"
          << std::endl;
      std::cin >> url;
      if (url == "exit") {
        break;
      } else {
        urls.push_back(url);
      }
    }
  } else if (input == 2) {
    std::cout << "AVISO: Se leerá un archivo con nombre \"urls.txt\" dentro de "
                 "la carpeta \"tests\" del repositorio."
              << std::endl;
    std::string file = "tests/urls.txt";
    std::ifstream filestream(file);
    if (!filestream.is_open()) {
      std::cerr << "Error al abrir el archivo " << std::endl;
    } else {
      std::stringstream buffer;
      buffer << filestream.rdbuf();
      filestream.close();
      std::string url;
      while (std::getline(buffer, url, '\n')) {
        urls.push_back(url);
      }
    }
  } else {
    std::cout << "Entrada inválida" << std::endl;
  }
  return urls;
}

// int main() {
// Mailbox correo;
// std::ostringstream oss;
// for (int i = 0; i <= 3000; ++i) {
//   oss << i;
//   if (i < 3000) {
//     oss << ", ";
//   }
// }
// std::string prueba1 = oss.str();

// std::ostringstream oss2;
// for (int i = 3000; i >= 0; --i) {
//   oss2 << i;
//   if (i > 0) {
//     oss2 << ", ";
//   }
// }
// std::string prueba2 = oss2.str();

// u_int reps = ceil(prueba1.size() / 4000.0);

// pid_t pid1 = fork();
// if (pid1 == -1) {
//   std::cout << "Error creating child process" << std::endl;
// } else if (pid1 == 0) {
//   correo.SendMsg(prueba1, reps);
//   exit(0);
// } else {
//   pid_t pid2 = fork();
//   if (pid2 == -1) {
//     std::cout << "Error creating child process" << std::endl;
//   } else if (pid2 == 0) {
//     correo.SendMsg(prueba2, reps);
//     exit(0);
//   } else {
//     std::string resultado1 = correo.RecieveMsg();
//     std::string resultado2 = correo.RecieveMsg();
//     std::cout << "Me llego esta picha del primer string: " << resultado1
//               << std::endl;
//     std::cout << "Me llego esta picha del segundo string: " << resultado2
//               << std::endl;
//   }
// }
// }