#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "GlobalAnalyzer.h"

std::vector<std::string>* initSource();

int main() {
  std::vector<std::string>* urls = initSource();
  if (urls == nullptr) {
    return 1;
  } else {
    GlobalAnalyzer* globalAnalyzer = new GlobalAnalyzer();
    globalAnalyzer->createProcesses(urls);
    globalAnalyzer->readMailbox();
  }
  return 0;
}

std::vector<std::string>* initSource() {
  std::vector<std::string>* urls = nullptr;
  int input;
  std::cout << "¿Desea introducir los URLs manualmente?\n1 para sí, 2 para no"
            << std::endl;
  std::cin >> input;
  if (input == 1) {
    urls = new std::vector<std::string>;
    std::cout << "Introduzca un URL para analizar su HTML" << std::endl;
    while (true) {
      std::string temp;
      std::cout
          << "Introduzca un URL o escriba \"exit\" si no desea agregar más"
          << std::endl;
      std::cin >> temp;
      if (temp == "exit") {
        break;
      } else {
        urls->push_back(temp);
      }
    }
  } else if (input == 2) {
    std::cout << "AVISO: Se leerá un archivo con nombre \"urls.txt\" dentro de "
                 "la carpeta \"src\" del repositorio."
              << std::endl;
    std::string file = "tests/urls.txt";
    std::ifstream filestream(file);
    if (!filestream.is_open()) {
      std::cerr << "Error al abrir el archivo " << std::endl;
      return nullptr;
    }
    std::stringstream buffer;
    buffer << filestream.rdbuf();
    filestream.close();
    std::string url;
    urls = new std::vector<std::string>;
    while (std::getline(buffer, url, '\n')) {
      urls->push_back(url);
    }
  } else {
    std::cout << "Entrada inválida" << std::endl;
    return nullptr;
  }
  // for (size_t i = 0; i < urls->size(); i++) {
  //   std::cout << urls->at(i) << std::endl;
  // }
  return urls;
}