#pragma once
#include <iostream>
#include <vector>
#include <string>

class Archivo {
  public:
  u_int size;
  std::string type;
  std::string nombre;
  std::vector<u_int> indices; /// Índices de los bloques de un archivo dentro del super bloque

  public:
    Archivo();
    Archivo(std::string nombre, std::string type);
    
    bool operator==(const Archivo& other) const {
      return this->nombre == other.nombre;
    }
};