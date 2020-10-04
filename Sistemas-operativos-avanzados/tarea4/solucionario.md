# Tarea de codificación 4



## Pregunta 5

+ Para acceder a `/a/b/c/orig.txt` tendremos que acceder a tres directorios(suponiendo que estamos en el directorio raíz).
+ Si creamos un enlace duro `/hard.txt <=> /a/b/c/orig.txt`, y accedemos desde `/` a `/hard.txt`, entonces no accedemos a ninguna carpeta. Recuerde que un 'enlace duro' no es más que una entrada en el directorio al mismo inode. Es decir, ambos son el mismo fichero pero se puede acceder a ellos desde ambas carpetas.
+ No. De hecho, la única diferencia que tiene con el fichero original es el nombre. Después de eso, ambos son igual de válidos. Es decir, no podemos decir que uno sea el original y otro una copia porque ambos son el mismo fichero.
+ Sí. Por lo explicado anteriormente.
+ Al ejecutar `ln -s /a/b/c/orig.txt /a/b/c/soft.txt`  y luego acceder a `/a/b/c/soft.txt`, desde el directorio raíz, entonces accederemos a 6 directorios.
+ Los _soft links_ son ficheros especiales que guardan información de su propio nombre y la ruta del fichero al que apunta. En este caso, sí podemos hablar de fichero original y fichero liga.
+ Una vez que se elimina el fichero original, el _soft link_ deja de ser válido porque guarda la ruta de un fichero que ya no existe.
+ No se puede crear un fichero liga de esa manera. El fichero tratará de buscar el directorio `a/b/c/` en la carpeta y no lo encontrará. Es decir, el _soft link_ no apuntará a nada.

