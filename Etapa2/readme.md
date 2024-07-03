# Etapa II Proyecto de Sistemas Operativos

## Integrantes

- Jose Mena C14653
- Brandon Trigueros C17899

## Descripción del problema

En este proyecto se intentó simular el cómo un sistema operativo gestiona los archivos en su disco duro mediante syscalls tomándo como archivos el recuento de las etiquetas de distintos URLs.

Las syscalls simuladas son proporcionadas por una clase llamada SuperBloque, la cual servirá como intermediario y será la única clase con acceso directo al disco.

Los procesos de parseo y modificación de los URLs solicitados lo harán distintos procesos creados desde un menú el cual será controlado por el usuario y sus preferencias.

Como intermediarios entre los procesos, su información y el disco se encuentran dos diferentes clases.

- Mailbox

Esta clase sirve como interfaz para paso de mensajes entre los múltiples posibles procesos creados por el usuario y el gestor intermediario entre el disco y el menú, el GlobalAnalyzer.

- GlobalAnalyzer

Esta clase obtendrá (de haberlos) todos los mensajes enviados al Mailbox por un proceso creado por el usuario y, además, accederá al disco mediante el uso de las syscalls proporcionadas por la interfaz disponible desde el SuperBloque.

## Flujo del programa

El programa incia desde la clase menú la cual es creada desde el main.

### Menú

El menú despliegará una interfaz legible para el usuario desde la terminal, la cual dispondrá de diferentes opciones para gestionar el disco.

**IMPORTANTE.**

Estas opciones se gestionan únicamente con la entrada de números, no con los nombres o el texto de las opciones.

### Opciones

#### - Analizar url

Si se selecciona analizar url podrá optar por leer el archivo del directorio "tests/urls.txt" con la entrada "test" el cual **debe de contener un url por linea** , de otra forma se estaría optando por escribir un URL personalizado manualmente en media ejecución del programa.

Una vez leido(s) el URL, se solicitara desde el GlobalAnalyzer que lea una cantidad determinada de archivos para, seguidamente, guardarlos en el disco.

#### - Ver estado del disco

Esta opción imprimirá el nombre de todos los archivos que se encuentren en el disco (de haber alguno) y luego se podrá escoger si se desea leer el contenido de alguno de estos, eliminarlo o incluso ver una representación de todos los bloques del disco con la opción "Ver Bloques".

Con la opción "Ver un archivo" se le pide al SuperBloque que muestre el contenido de un determinado archivo con el nombre suministrado desde la terminal.

Similar a la opción "Ver un archivo", la opción "Eliminar un archivo" eliminará un archivo del disco dejando sus bloques libres para ser usados por si el usuario desea analizar más URLs.

#### - Salir

Esta opción termina con la ejecución del programa.

## Manual de uso

- Clonar el repositorio desde el link de git <https://github.com/BrandonTrigueros/TareaProgramadaSO.git>
- Entrar a la carpeta Etapa2
- Desde ahí ejecutar el siguiente comando en bash

```bash
make
./bin/Etapa2
```

Esto despliegará un menú con indicaciones para el uso de las diferentes funcionalidades del programa.

## Indicaciones

- Este código sólo esta hecho para ser compilado y corrido en el sistema operativo Fedora
- Este código no está pensado para desencriptar cifrados SSL de las páginas suministradas

## Documentación en Doxygen

Ya que este proyecto genera documentación utilizando Doxygen, se puede acceder a una explicación de las clases desde el navegador abriendo el siguiente enlace:

[Documentación de MyProject](./doc/html/index.html)
