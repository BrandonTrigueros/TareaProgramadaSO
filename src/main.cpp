#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "Analyzer.h"

std::vector<std::string>* initSource();

int main() {
  std::vector<std::string>* urls = initSource();
  if (urls == nullptr) {
    return 1;
  } else {
    // create Global Analyzer
    for (size_t i = 0; i < urls->size(); i++) {
      int pid = fork();
      if (pid == -1) {
        std::cout << "Se tensó xd" << std::endl;
        return 1;
      } else if (pid == 0) {
        std::cout << "Soy un hijo, chat" << std::endl;
        // **** asigno un url ****
        ReadHtml(urls->at(i));
        break;
      } else {
        std::cout << "Soy admin :v" << std::endl;
      }
    }
  }
  return 0;
}

std::vector<std::string>* initSource() {
  std::vector<std::string>* urls = nullptr;
  int entrada;
  std::cout << "¿Desea introducir los URLs manualmente?\n1 para sí, 2 para no"
            << std::endl;
  std::cin >> entrada;

  if (entrada == 1) {
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

  } else if (entrada == 2) {
    std::cout << "AVISO: Se leerá un archivo con nombre \"urls.txt\" dentro de "
                 "la carpeta \"src\" del repositorio."
              << std::endl;
    std::string archivin = "tests/urls.txt";
    std::ifstream archivo(archivin);
    if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo " << std::endl;
      return nullptr;
    }
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();
    std::string url;
    urls = new std::vector<std::string>;
    while (std::getline(buffer, url, '\n')) {
      urls->push_back(url);
    }

  } else {
    std::cout << "Entrada inválida" << std::endl;
    return nullptr;
  }

  for (size_t i = 0; i < urls->size(); i++) {
    std::cout << urls->at(i) << std::endl;
  }
  return urls;
}
