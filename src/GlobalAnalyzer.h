#pragma once

#include "Analyzer.h"

#include <iostream>
#include <map>
#include <unistd.h>

class GlobalAnalyzer {

  private:
  Mailbox* mailbox;
  std::vector<std::string>* urls;
  std::map<std::string, std::map<std::string, int>>* url_maps;

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();

  void createProcesses(std::vector<std::string>* urls);
  std::map<std::string, int> analyzeTags(std::string tags);
  void readMailbox();
};
