#pragma once

#include <iostream>
#include <map>
#include <vector>

/**
 *
 */
typedef struct Message {
  void* data;
  size_t sender_pid;
} Message_t;
