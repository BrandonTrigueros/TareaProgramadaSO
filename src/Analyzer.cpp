#include "Analyzer.h"
// std::map<std::string, int>*

void ReadHtml(std::string url) {
  std::string nombreArchivo = "tests/test.txt";
  std::ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo " << std::endl;
    return;
  }
  std::stringstream buffer;
  buffer << archivo.rdbuf();
  archivo.close();
  std::string contenido = buffer.str();
  // std::cout << "Contenido del archivo:\n" << contenido << std::endl;
  std::regex etiqueta_regex("<([^>]*)>");
  std::smatch coincidencias;
  std::string::const_iterator inicio = contenido.cbegin();
  std::string::const_iterator fin = contenido.cend();
  std::map<std::string, int>* etiquetas = new std::map<std::string, int>;
  while (std::regex_search(inicio, fin, coincidencias, etiqueta_regex)) {
    auto it = etiquetas->find(coincidencias[1].str());
    if (it == etiquetas->end()) {
      etiquetas->insert({ coincidencias[1].str(), 1 });
    } else {
      it->second++;  // Si la etiqueta existe, incrementar su valor en 1
    }
    inicio = coincidencias.suffix().first;
  }

  std::map<std::string, int>::iterator it = etiquetas->begin();
  while (it != etiquetas->end()) {
    std::cout << "Etiqueta <" << it->first << "> encontrada " << it->second
              << " veces." << std::endl;
    ++it;
  }
  delete etiquetas;
}
