#pragma once

#include "Analyzer.h"

#include <iostream>
#include <map>
#include <unistd.h>

/**
 * @brief Clase que se encarga de crear procesos hijos para analizar las URLs
 * y almacenar las etiquetas de los HTMLs en un mapa.
 */
class GlobalAnalyzer {

  private:
  Mailbox* mailbox;  /// Buzón de paso de mensajes.
  std::vector<std::string>* urls;  /// Vector de URLs a analizar.
  std::map<std::string, std::map<std::string, int>>* url_maps;  /// Mapa de url

  public:
  /**
   * @brief Constructor para la clase GlobalAnalyzer.
   */
  GlobalAnalyzer();
  /**
   * @brief Destructor para la clase GlobalAnalyzer.
   */
  ~GlobalAnalyzer();

  /**
   * @brief Crea un proceso hijo por cada URL en el vector de URLs. Cada proceso
   * hijo se encarga de hacer request a la URL y enviar las etiquetas del HTML
   * al buzon.
   * @param urls Vector of URLs to analyze.
   */
  void createProcesses(std::vector<std::string>* urls);
  /**
   * @brief Obtiene uns string con las etiquetas del HTML y las cuenta para
   * agregarlas a un map.
   * @return El mapa con las etiquetas y su cantidad.
   */
  std::map<std::string, int> analyzeTags(std::string tags);
  /**
   * @brief Lee el buzon de mensajes y almacena las etiquetas que obtuvieron los
   * procesos hijos.
   */
  void readMailbox();
};
