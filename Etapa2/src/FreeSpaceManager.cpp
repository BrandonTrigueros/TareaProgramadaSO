#include "FreeSpaceManager.h"

FreeSpaceManager::FreeSpaceManager() { free_blocks.reset(); }

FreeSpaceManager::~FreeSpaceManager() { }

void FreeSpaceManager::reserveBlock(u_int block) { free_blocks[block] = 1; }

void FreeSpaceManager::releaseBlock(u_int block) { free_blocks[block] = 0; }

u_int FreeSpaceManager::getFreeBlock() {
  for (u_int i = 0; i < free_blocks.size(); i++) {
    if (free_blocks[i] == 0) {
      return i;
    }
  }
  return -1;
}

void FreeSpaceManager::print() {
  for (u_int i = 0; i < free_blocks.size(); i++) {
    if (free_blocks[i] == 0) {
      std::cout << "□";
    } else {
      std::cout << "■";
    }
  }
  std::cout << std::endl;
}