#pragma once

#include <limits>
#include <map>
#include <string>

#include "Archivo.h"

/**
 * @brief Tabla de gestión de los archivos abiertos del disco.
 */
class TableStructure {
  public:
  std::map<u_int, Archivo*> open_files; /// Mapa de los archivos abiertos.

  TableStructure();

  ~TableStructure();

  /**
   * @brief Agrega un archivo al mapa de los archivos abiertos.
   * @param arch Archivo que será agregado a la tabla.
   */
  void addEntrie(Archivo* arch);

  /**
   * @brief Elimina un archivo de la tabla de archivos abiertos.
   * @param index Índice del archivo que será retirado de la tabla.
   */
  void removeEntrie(u_int index);

  /**
   * @brief Obtiene el file descriptor de un archivo.
   * @param nombre Nombre del archivo al cual se le quiere averiguar su file descriptor.
   * @return Retorna el file descriptor del archivo.
   */
  u_int getFD(std::string nombre);

  /**
   * @brief Indica si un archivo está actualmente abierto.
   * @param fd File descriptor del archivo que se quiere comprobar si está abierto.
   */
  std::string isFileOpen(u_int fd);

  /**
   * @brief Indica el tamaño de un archivo.
   * @param fd File descriptor del archivo al que se le quiere comprobar su tamaño.
   */
  u_int getSize(u_int fd);
};