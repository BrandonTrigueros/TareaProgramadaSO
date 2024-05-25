#pragma once

#include "Analyzer.h"
#include "Mailbox.h"

#include <iostream>
#include <map>
#include <unistd.h>

class GlobalAnalyzer {

  private:
  Mailbox& mailbox;
  std::vector<int> pids;
  std::vector<std::string>* urls;

  std::map<std::string, int>* url_totalTags;
  std::map<std::string, std::map<std::string, int>*>* url_maps;

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();

  void createProcesses(std::vector<std::string>* urls);
  void readMailbox();
};
