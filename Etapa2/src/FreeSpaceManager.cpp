#include "FreeSpaceManager.h"

FreeSpaceManager::FreeSpaceManager() {
      free_blocks.reset(0);
    }
u_int FreeSpaceManager::getFreeBlock() {
  return free_blocks._Find_first();
}
void FreeSpaceManager::reserveBlock(u_int block) {
  free_blocks[block] = 1;
}
void FreeSpaceManager::releaseBlock(u_int block) {
  free_blocks[block] = 0;
}