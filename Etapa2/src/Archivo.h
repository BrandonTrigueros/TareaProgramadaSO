#pragma once
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Formato de la información de los archivos guardados en disco.
 */
class Archivo {
  public:
  u_int size; /// Tamano total del archivo.
  std::string type; /// Tipo del archivo.
  std::string nombre; /// Nombre identificador del archivo.
  std::vector<u_int>
      indices;  /// Índices de los bloques de un archivo dentro del super bloque.

  public:
  Archivo();
  
  Archivo(std::string nombre, std::string type);

  Archivo(const Archivo& other) {
    this->nombre = other.nombre;
    this->type = other.type;
    this->size = other.size;
    this->indices = other.indices;
  }

  bool operator==(const Archivo& other) const {
    return this->nombre == other.nombre;
  }


  Archivo& operator=(const Archivo& other) {
    this->nombre = other.nombre;
    this->type = other.type;
    this->size = other.size;
    this->indices = other.indices;
    return *this;
  }
};
