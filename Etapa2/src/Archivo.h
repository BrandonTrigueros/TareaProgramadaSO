#pragma once
#include <iostream>
#include <string>
#include <vector>

class Archivo {
  public:
  u_int size;
  std::string type;
  std::string nombre;
  std::vector<u_int>
      indices;  /// Índices de los bloques de un archivo dentro del super bloque

  public:
  Archivo();
  Archivo(std::string nombre, std::string type);

  bool operator==(const Archivo& other) const {
    return this->nombre == other.nombre;
  }

  Archivo(const Archivo& other) {
    this->nombre = other.nombre;
    this->type = other.type;
    this->size = other.size;
    this->indices = other.indices;
  }

  Archivo& operator=(const Archivo& other) {
    this->nombre = other.nombre;
    this->type = other.type;
    this->size = other.size;
    this->indices = other.indices;
    return *this;
  }
};