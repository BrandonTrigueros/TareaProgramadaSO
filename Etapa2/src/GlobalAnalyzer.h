#pragma once

#include "Mailbox.h"
#include "SuperBloque.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>

/**
 * @brief Intermediario entre procesos que quieren acceder al disco.
 */
class GlobalAnalyzer {
  private:
  Mailbox mailbox; /// Mailbox para el paso de mensajes entre los procesos que analizan las URL.

  SuperBloque superBloque; /// Interfaz de acceso al disco con sus syscalls simuladas.

  Semaphore canConsume; /// Semáforo de acceso al mailbox.

  public:
  GlobalAnalyzer();

  ~GlobalAnalyzer();

  /**
   * @brief Setter para el mailbox de la clase.
   * @param mailbox Objeto mailbox para setear el atributo de la clase.
   */
  void setMailbox(Mailbox& mailbox);

  /**
   * @brief Setter para el semáforo de la clase.
   * @param canConsume Objeto semaphore para setear el atributo de la clase.
   */
  void setSemaphore(Semaphore& canConsume);

  /**
   * @brief Recibe una cantidad determinada de mensajes del mailbox.
   * @param numMessages Cantidad de mensajes que se leerán del mailbox.
   */
  void recibirMensajes(u_int numMessages);

  /**
   * @brief Guarda en el disco un archivo de texto.
   * @param nombre Nombre del archivo de texto que se quiere guardar en el disco.
   * @param data Texto que será guardado en el disco.
   */
  void guardarEnDisco(std::string nombre, std::string data);

  /**
   * @brief Elimina un archivo del disco.
   * @param nombre NOmbre identificador del archivo que se quiere eliminar del disco.
   */
  void eliminarArchivo(std::string nombre);

  /**
   * @brief Lee el contenido de un archivo del disco.
   * @param nombre Nombre identificador del archivo del disco que se quiere leer.
   */
  void leerArchivo(std::string nombre);

  /**
   * @brief Muestra el nombre de los archivos almacenados en el disco.
   */
  void showDiskFiles();

  /**
   * @brief Imprime una representación de los bloques libres y ocupados del disco.
   */
  void printDisk();
};
