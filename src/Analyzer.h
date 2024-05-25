#pragma once

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

class Analyzer {
  public:
  Analyzer();
  ~Analyzer();
  void Connect(std::string url);
  std::map<std::string, int>* GetMap(std::string url);

  private:
  std::string GetHTML(std::string url);
  std::map<std::string, int>* AnalizeHTML(std::string html);
};
