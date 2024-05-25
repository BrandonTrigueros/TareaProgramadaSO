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
      std::map<std::string, int>* myMap = analyzer->getMap(urls->at(i));
      analyzer->sendMessage(myMap, this->mailbox);
      exit(0);
    } else {
      this->pids.push_back(pid);
    }
  }
}

void GlobalAnalyzer::readMailbox() {
  for (size_t i = 0; i < this->pids.size(); i++) {
    Message_t message = this->mailbox.RecieveMsg();
    std::map<std::string, int>* tags
        = (std::map<std::string, int>*)message.data;
    std::cout << "Message recieved from child number: " << message.sender_pid
              << std::endl;
    this->url_maps->insert({ this->urls->at(i), tags });
    for (auto it = tags->begin(); it != tags->end(); it++) {
      auto it_total = this->url_totalTags->find(it->first);
      if (it_total == this->url_totalTags->end()) {
        this->url_totalTags->insert({ it->first, it->second });
      } else {
        it_total->second += it->second;
      }
    }
  }

  // print both maps
  std::cout << "Total tags:" << std::endl;
  for (auto it = this->url_totalTags->begin(); it != this->url_totalTags->end();
       it++) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
  std::cout << "Tags per URL:" << std::endl;
  for (auto it = this->url_maps->begin(); it != this->url_maps->end(); it++) {
    std::cout << it->first << ":" << std::endl;
    for (auto it2 = it->second->begin(); it2 != it->second->end(); it2++) {
      std::cout << it2->first << ": " << it2->second << std::endl;
    }
  }
}