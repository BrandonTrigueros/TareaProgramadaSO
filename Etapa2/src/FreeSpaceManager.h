#pragma once

#include <bitset>

class FreeSpaceManager {
  private:
    std::bitset<512 * 1024> free_blocks;
  public:
    FreeSpaceManager();
    u_int getFreeBlock();
    void reserveBlock(u_int block);
    void releaseBlock(u_int block);
};