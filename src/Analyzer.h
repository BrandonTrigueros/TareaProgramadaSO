#pragma once

#include "Mailbox.h"

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

/**
 * @brief Clase con los métodos necesarios para pedir el código HTML a las
 * páginas y convertirlo a un string con sus etiquetas.
 */
class Analyzer {
  public:
  Analyzer();
  ~Analyzer();

  /**
   * @brief Método que convierte un URL en un string con las etiquetas del HTML.
   * @param url URL de la página a analizar.
   * @return Retorna un string con todas las etiquetas del HTML de la página.
   */
  std::string getString(std::string url);

  /**
   * @brief Método que envia las etiquetas de la página de un URL a un buzon de
   * paso de mensajes.
   * @param url URL de la página a analizar.
   * @param mailbox Buzón para paso de mensajes entre procesos.
   */
  void sendMessage(std::string url, Mailbox* mailbox);

  private:
  /**
   * @brief Obtiene el HTML de una página.
   * @param url Link de la página a la que se le pedirá el HTML.
   * @return Retorna el HTML de la página.
   */
  std::string getHTML(std::string url);

  /**
   * @brief Analiza un HTML para juntar todas sus etiquetas en un string.
   * @param html HTML de la página en formato string.
   * @return Retorna las etiquetas del HTML en un string.
   */
  std::string analizeHTML(std::string html);
};
