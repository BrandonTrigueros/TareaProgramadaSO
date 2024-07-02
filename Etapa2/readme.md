# Etapa II Proyecto de Sistemas Operativos

## Integrantes

- Jose Mena C14653
- Brandon Trigueros C17899

## Descripción del problema

En este proyecto se intentó simular el cómo un sistema operativo gestiona los archivos en su disco duro mediante syscalls tomándo como archivos el recuento de las etiquetas de distintos URLs.

Estas etiqutas se guardarán en el disco duro mediante una estructura de "SuperBloque" el cual se conforma de varios bloques que no son otra cosa más que chars* de tamaño 64 que almacenan la información que se quiera guardar fragmentada entre todo el disco.

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
