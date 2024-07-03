#include "Archivo.h"

Archivo::Archivo() {
  this->nombre = "";
  this->type = "";
  this->size = 0;
}

Archivo::Archivo(std::string nombre, std::string type) {
  this->nombre = nombre;
  this->type = type;
  this->size = 0;
}