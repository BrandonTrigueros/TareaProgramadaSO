#ifndef GLOBALANALYZER_H
#define GLOBALANALYZER_H

#include "Mailbox.cpp"

#include <iostream>
#include <map>

class GlobalAnalyzer {

  private:
  Mailbox& mailbox;
  std::vector<std::string>* urls;
  std::map<std::string, int>* url_totalTags;
  std::map<std::string, std::map<std::string, int>*>* url_maps;

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();

  void createProcesses(std::vector<std::string>* urls);
  void waitProcesses();
};

#endif  // GLOBALANALYZER_H
