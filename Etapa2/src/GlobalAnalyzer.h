#pragma once

#include <iostream>
#include <map>
#include <unistd.h>

class GlobalAnalyzer {
  private:
  // std::map<std::string, std::map<std::string, int>> url_maps;  /// Mapa de
  // urls

  public:
  GlobalAnalyzer();
  ~GlobalAnalyzer();
  void readMailbox();

  private:
  void guardarArchivo(std::string nombreArchivo);
};