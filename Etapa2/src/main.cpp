#include "Mailbox.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

std::vector<std::string> initSource();

int main() {
  Mailbox correo;
  char* prueba1 = new char[6000];
  for (int i = 0; i < 6000; i++) {
    prueba1[i] = (i % 10) + 48;
  }
  // std::cout << prueba1 << std::endl;
  char* prueba2 = new char[6000];
  for (int i = 0; i < 6000; i++) {
    prueba2[i] = ((6000 - i) % 10) + 48;
  }
  double repeticiones = 6000 / 4040.0;
  pid_t pid1 = fork();
  if (pid1 == -1) {
    std::cout << "Error creating child process" << std::endl;
    return 1;
    // Si soy un proceso hijo, envío un mensaje con las etiquetas
  } else if (pid1 == 0) {
    correo.SendMsg(prueba1, (u_int)ceil(repeticiones), 1);
    return 0;
  }
  pid_t pid2 = fork();
  if (pid2 == -1) {
    std::cout << "Error creating child process" << std::endl;
    return 1;
    // Si soy un proceso hijo, envío un mensaje con las etiquetas
  } else if (pid2 == 0) {
    correo.SendMsg(prueba2, (u_int)ceil(repeticiones), 1);
    return 0;
  }
  char* resultado1;
  char* resultado2;
  correo.RecieveMsg(resultado1);
  std::cout << "Me llego esta picha del primer string:\n"
            << resultado1 << std::endl;
  correo.RecieveMsg(resultado2);
  std::cout << "Me llego esta picha del segundo string:\n"
            << resultado2 << std::endl;
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
