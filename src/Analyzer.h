#pragma once

#include "Mailbox.h"
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
  std::map<std::string, int>* getMap(std::string url);
  void sendMessage(std::map<std::string, int>* tags, Mailbox& mailbox);

  private:
  std::string getHTML(std::string url);
  std::map<std::string, int>* analizeHTML(std::string html);
};
