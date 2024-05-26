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
  std::string getString(std::string url);
  void sendMessage(std::string url, Mailbox* mailbox);

  private:
  std::string getHTML(std::string url);
  std::string analizeHTML(std::string html);
};
