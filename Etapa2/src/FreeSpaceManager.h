#pragma once

#include <bitset>
#include <iostream>

/**
 * @brief Gestor de espacio del disco.
 */
class FreeSpaceManager {
  private:
  std::bitset<512 * 1024> free_blocks; /// Representación de los bloques libres del disco.

  public:
  FreeSpaceManager();

  ~FreeSpaceManager();

  /**
   * @brief Indica el próximo bloque libre en el disco.
   * @return Retorna el índice del próximo bloque libre del disco.
   */
  u_int getFreeBlock();

  /**
   * @brief Reserva un bloque del disco.
   * @param block índice que quiere ser reservado en el disco.
   */
  void reserveBlock(u_int block);

  /**
   * @brief Libera un bloque en el disco.
   * @param block Índice del bloque que quiere ser liberado en el disco.
   */
  void releaseBlock(u_int block);

  /**
   * @brief Imprime una representación de los bloques libres y vacios del disco.
   */
  void print();
};
