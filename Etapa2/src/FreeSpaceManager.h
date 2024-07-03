#pragma once

#include <bitset>
#include <iostream>

class FreeSpaceManager {
  private:
  std::bitset<512 * 1024> free_blocks;

  public:
  FreeSpaceManager();
  ~FreeSpaceManager();
  u_int getFreeBlock();
  void reserveBlock(u_int block);
  void releaseBlock(u_int block);
  void print();
};