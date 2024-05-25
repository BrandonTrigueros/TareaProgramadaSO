#include "GlobalAnalyzer.h"

GlobalAnalyzer::GlobalAnalyzer()
    : mailbox(Mailbox::getInstance()) {
  this->urls = new std::vector<std::string>;
  this->url_maps = new std::map<std::string, std::map<std::string, int>*>;
}

GlobalAnalyzer::~GlobalAnalyzer() {
  delete this->urls;
  delete this->url_totalTags;
  for (auto it = this->url_maps->begin(); it != this->url_maps->end(); it++) {
    delete it->second;
  }
  delete this->url_maps;
}

void GlobalAnalyzer::createProcesses(std::vector<std::string>* urls) {
  this->urls = urls;
  for (size_t i = 0; i < urls->size(); i++) {
    pid_t pid = fork();
    if (pid == -1) {
      std::cout << "Error creating child process" << std::endl;
      return;
    } else if (pid == 0) {
      Analyzer* analyzer = new Analyzer();
      std::map<std::string, int>* myMap = analyzer->GetMap(urls->at(i));
      exit(0);
    } else {
      this->pids.push_back(pid);
    }
  }
}
