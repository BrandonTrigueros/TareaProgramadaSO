#pragma once

#include "Socket.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <regex>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Analyzer {
  public:
  Analyzer();
  ~Analyzer();
  std::map<std::string, int>* GetMap(std::string url);

  private:
  std::string GetHTML(std::string url);
  std::map<std::string, int>* AnalizeHTML(std::string html);
};
