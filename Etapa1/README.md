# Tarea Programada Sistemas Operativos CI-0122 Parte 1 Grupo 1

## Autores
- Jose Carlos Mena C14653
- Brandon Trigueros C17899

## Manual de uso

### Importante
- Este código está hecho para ser compilado en el sistema operativo Fedora.
- De querer entrar a otras páginas, se deben agregar en el archivo tests/urls.txt.
- Se soportan solo links no mayores a 256 caracteres.
- Se soportan solo páginas con HTMLs que no posean más de 7600 caracteres de etiquetas.

### Como compilar
Ejecutar el siguiente comando en una terminal en la carpeta del re
```bash
make clean; make
./bin/Sistemas
```
Luego en la terminal se darán las instrucciones posteriores.

## Explicación del código
El programa empieza con el proceso padre, el cual obtiene los URLs suministrados por el usuario. Luego este procede a crear un proceso con fork() por cada URL obtenido.
Los procesos hijos van a la función sendMessage() administrada por la clase analyzer, la cual se va a dedicar especialmente en intentar establecer conexión con la página del URL, extraer su código HTML y pasarlo todo a un string. Este string es analizado para dejarlo solo con las etiquetas para seguidamente ser enviado a una cola de mensajes entre procesos.

El proceso padre una vez creado todos los procesos hijos va a la función readMailbox() la cual se quedará intentando leer mensajes del buzón hasta que haya leido tantos strings con etiquetas como URLs obtenidos en un principio. Este contará cada etiqueta y las veces que aparece en el string para cada URL para, al final, imprimir los resultados.
