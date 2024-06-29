#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "GlobalAnalyzer.h"

std::vector<std::string> initSource();

int main() {
  std::vector<std::string> urls = initSource();
  if (urls.empty()) {
    return 1;
  } else {
    GlobalAnalyzer globalAnalyzer;
    // Creo procesos
    globalAnalyzer.createProcesses(urls);
    // Leo los mensajes de los procesos hijos
    globalAnalyzer.readMailbox();
  }
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