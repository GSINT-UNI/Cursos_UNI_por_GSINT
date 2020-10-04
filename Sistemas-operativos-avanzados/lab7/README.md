## Notas del laboratorio 7 CC-571

En las notas veremos los siguientes temas:

* Dispositivos de entrada y salida
* Archivos y directorios
* Implementación de sistemas de archivos
* HDD

### Observaciones

* Todo el código fuente es parte del libro:  Operating Systems: Three Easy Pieces  de Remzi H. Arpaci-Dusseau y Andrea C. Arpaci-Dusseau, alojado en  [https://github.com/remzi-arpacidusseau/ostep-code](https://github.com/remzi-arpacidusseau/ostep-code). 
* Se usa el código con fines didácticos.

### Dispositivo de entradas y salida

1. Cuando aparecen múltiples interrupciones de diferentes dispositivos aproximadamente al mismo tiempo, se puede utilizar un esquema de prioridad para determinar el orden en el que se atenderán las interrupciones. Discute qué problemas deben ser considerado al asignar prioridades a diferentes interrupciones.
2. ¿Cuáles son las ventajas y desventajas de admitir E/S asignadas en memoria a los registros de control de dispositivos?
3. En la mayoría de los sistemas multiprogramados, los programas de usuario acceden a la memoria a través de direcciones virtuales, mientras que el sistema operativo utiliza direcciones físicas sin procesar para acceder a la memoria. ¿Cuáles son las implicaciones de este diseño en el inicio de operaciones de E/S por el programa de usuario y su ejecución por el sistema operativo?
4. Describe tres circunstancias bajo las cuales se debe usar el bloqueo de E/S. Describe tres circunstancias en las que se deben utilizar las E/S sin bloqueo. ¿Por qué no simplemente implementar E/S sin bloqueo y hacer que los procesos estén en modo busy-wait hasta que su dispositivo esté listo?.
5. Algunos controladores DMA admiten el acceso directo a la memoria virtual, donde los targets de las operaciones de E/S se especifican como direcciones virtuales y se realiza una traducción de la dirección virtual a la física durante el DMA. ¿Cómo complica este diseño el diseño del controlador DMA? ¿Cuáles son las ventajas de proporcionar esta funcionalidad?.

### Archivos y directorios

1. Analiza la versión del programa  de línea de comandos *stat*, que simplemente llama a  *stat()* en un archivo o directorio determinado (corregir su fuese necesario). Imprime el tamaño del archivo, el número de bloques asignados, el conteo  de referencias (link), etc. ¿Cuál es el conteo de enlaces de un directorio, a medida que cambia el número de entradas en el directorio? 

   ```c
   #include <stdio.h>     
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>
   #include <stdlib.h>    
   #include <time.h>   
   
   int main(int argc, char *argv[]) {
       struct stat sb;
   
       if (argc != 2) {
           fprintf(stderr, "Uso: %s <ruta>\n", argv[0]);
           exit(EXIT_FAILURE);
       }
   
       if (stat(argv[1], &sb) == -1) {
           perror("stat");
           exit(EXIT_FAILURE);
       }
   
       printf("Tipo de archivo:  ");
       switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:
               printf("bloque de dispositivo\n");
               break;
           case S_IFCHR:
               printf("Dispositivo-caracter\n");
               break;
           case S_IFDIR:
               printf("directorio\n");
               break;
           case S_IFIFO:
               printf("FIFO/pipe\n");
               break;
           case S_IFLNK:
               printf("Enlace simbolico\n");
               break;
           case S_IFREG:
               printf("Archivo regular\n");
               break;
           case S_IFSOCK:
               printf("socket\n");
               break;
           default:
               printf("Desconocido?");
               break;
       }
   
       printf("Numero I-nodo:            %ld\n", (long) sb.st_ino);
       printf("Modo:                     %lo (octal)\n", (unsigned long) sb.st_mode);
       printf("Conteo de enlaces:               %ld\n", (long) sb.st_nlink);
       printf("Propiedad:                UID=%ld    GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
       printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
       printf("Archivos:                %lld bytes\n", (long long) sb.st_size);
       printf("Bloques asignados:         %lld\n", (long long) sb.st_blocks);
       printf("Ultimo cambio de estado:       %s", ctime(&sb.st_ctime));
       printf("Ultimo acceso al archivo:         %s", ctime(&sb.st_atime));
       printf("Ultima modificacion de archivo:   %s", ctime(&sb.st_mtime));
   
       exit(EXIT_SUCCESS);
   }
   ```

2. Analiza y corrige si fuese necesario, el siguiente programa que enumere los archivos en el directorio dado. Cuando se llama sin argumentos, el programa debe imprimir los nombres de los archivos. Cuando se invoca con la bandera -l, el programa debe imprimir información sobre cada archivo, como el propietario, el grupo, los permisos y otra información obtenida de la llamada al sistema *stat()*. El programa debe tomar un argumento adicional, que es el directorio a leer, por ejemplo, *myls -l directorio*. Si no se proporciona un directorio, el programa debería usar el directorio de trabajo actual. 

   ```c
   #include <stdio.h>     
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>   
   #include <stdlib.h>  
   #include <dirent.h>  
   #include <string.h>   
   #include <stdbool.h>
   #include <time.h>    
   
   #define STRINGSIZE 1024
   #define handle_error(msg) \
       do { perror(msg); exit(EXIT_FAILURE); } while (0)
   
   void print_file(struct stat sb) {
       printf("%4lo  ", (unsigned long) sb.st_mode);
       printf("%3ld  ", (long) sb.st_nlink);
       printf("%3ld  %3ld  ", (long) sb.st_uid, (long) sb.st_gid);
       printf("%4lld  ", (long long) sb.st_size);
       char timeString[STRINGSIZE] = "";
       strftime(timeString, STRINGSIZE, "%b %d %H:%M", localtime(&sb.st_mtime));
       printf("%s  ", timeString);
   }
   
   int main(int argc, char *argv[]) {
       struct stat sb;
       int opt;
       char * pathname = ".";
       bool list = false;
       DIR *dp;
       opterr = 0; 
   
       while ((opt = getopt(argc, argv, "l:")) != -1) {
           switch (opt) {
               case 'l':
                   pathname = optarg;
                   list = true;
                   break;
               case '?':
                   if (optopt == 'l')
                       list = true;
                   break;
               default:
                   break;
           }
       }
   
       if (!list && argc > 1)
           pathname = argv[1];
       
       if (stat(pathname, &sb) == -1)
           handle_error("stat");
   
       if (S_ISDIR(sb.st_mode)) {
           if ((dp = opendir(pathname)) == NULL)
               handle_error("opendir");
           struct dirent *d;
           while ((d = readdir(dp)) != NULL) {
               if (list) {
                   char filePath[STRINGSIZE] = "";
                   strncpy(filePath, pathname, strlen(pathname));
                   strncat(filePath, "/", 1);
                   strncat(filePath, d->d_name, strlen(d->d_name));
                   if (stat(filePath, &sb) == -1)
                       handle_error("stat");
                   print_file(sb);
               }
               printf("%s\n", d->d_name);
           }
           closedir(dp);
       } else {
           if (list)
               print_file(sb);
           printf("%s\n", pathname);
       }
   
       exit(EXIT_SUCCESS);
   }
   ```

3. Analiza y corrige si fuese necesario, el siguiente  programa que imprima las últimas líneas de un archivo. El programa debe ser eficiente, ya que busca acercarse al final del archivo, lee un bloque de datos y luego retrocede hasta encontrar el número de líneas solicitado. En este punto, debería imprimir esas líneas desde el principio hasta el final del archivo. Para invocar el programa, se debe escribir: mytail -n archivo, donde n es el número de líneas al final del archivo a imprimir. 

   ```c
   #include <stdio.h>     
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>    
   #include <stdlib.h>    
   #include <fcntl.h>    
   #include <string.h>
   
   #define handle_error(msg) \
       do { perror(msg); exit(EXIT_FAILURE); } while (0)
   
   int main(int argc, char *argv[]) {
       struct stat sb;
       int fd, offset, lines;
       char * pathname = "";
   
       if (argc != 3 || strlen(argv[1]) <= 1 || argv[1][0] != '-') {
           fprintf(stderr, "Uso: %s -<offset> <ruta-archivo>\n", argv[0]);
           exit(EXIT_FAILURE);
       }
   
       lines = atoi(argv[1]);
       lines *= -1;
       lines++;
       pathname = argv[2];
   
       if (stat(pathname, &sb) == -1)
           handle_error("stat");
   
       if ((fd = open(pathname, O_RDONLY)) == -1)
           handle_error("open");
   
       if (lseek(fd, -1, SEEK_END) == -1)
           handle_error("lseek");
   
       char buff[sb.st_size];
       while (lines > 0) {
           if (read(fd, buff, 1) == -1)
               handle_error("read");
           if (buff[0] == '\n')
               lines--;
           offset = lseek(fd, -2, SEEK_CUR);
           if (offset == -1)
               break;
       }
   
       if (offset > 0 || lines == 0) {
           if (lseek(fd, 2, SEEK_CUR) == -1)
               handle_error("lseek");
       } else {
           if (lseek(fd, 0, SEEK_SET) == -1)
               handle_error("lseek");
       }
   
       memset(buff, 0, sb.st_size);
       if (read(fd, buff, sb.st_size) == -1)
           handle_error("read");
   
       printf("%s", buff);
       close(fd);
   
       exit(EXIT_SUCCESS);
   }
   ```

### Implementación de sistemas de archivos

Utiliza esta herramienta,*vsfs.py*, para estudiar cómo cambia el estado del sistema de archivos a medida que se realizan diversas operaciones. El sistema de archivos comienza en un estado vacío, con solo un directorio raíz. A medida que se lleva a cabo la simulación, se realizan varias operaciones, cambiando así lentamente el estado en disco del sistema de archivos.

Las posibles operaciones son:

* mkdir() - crea un nuevo directorio
* creat(): crea un archivo nuevo (vacío)
* open(), write(), close(): agrega un bloque a un archivo
*  link(): crea un enlace fijo a un archivo
*  unlink() - desvincula un archivo (eliminándolo si linkcnt == 0)

Para comprender cómo funciona esta tarea, primero debes comprender cómo se representa el estado en disco de este sistema de archivos. El estado del sistema de archivos se muestra imprimiendo el contenido de cuatro estructuras de datos diferentes:

* Inode bitmap: indica qué inodos están asignados
* Inodos: tabla de inodos y su contenido
* data bitmap: indica qué bloques de datos están asignados
* data: indica el contenido de los bloques de datos

Los mapas de bits (bitmaps) deben ser bastante sencillos de entender, con un 1 que indica que el inodo o bloque de datos correspondiente está asignado y un 0 que indica que dicho inodo o bloque de datos está libre.

Cada uno de los inodos tiene tres campos: el primer campo indica el tipo de archivo (por ejemplo, f para un archivo normal, d para un directorio); el segundo indica qué bloque de datos pertenece a un archivo (aquí, los archivos solo pueden estar vacíos, por lo que tendrías la dirección del bloque de datos configurada en -1, o un bloque de tamaño, que tendría una dirección no negativa); el tercero muestra el conteo de referencias para el archivo o directorio. 

Por ejemplo, el siguiente inodo es un archivo normal, que está vacío (el campo de dirección se establece en -1) y solo tiene un enlace en el sistema de archivos:

```python
[f a: -1 r: 1]
```

Si el mismo archivo tuviera un bloque asignado (digamos el bloque 10), se mostraría de la siguiente manera:

```python
[f a: 10 r: 1]
```

Si alguien creara un enlace duro a este inodo, entonces se convertiría en:

 ```python
[f a: 10 r: 2]
 ```

Finalmente, los bloques de datos pueden retener datos de usuario o datos de directorio. Si se llena con datos de directorio, cada entrada dentro del bloque tiene el formato (nombre, número), donde "nombre" es el nombre del archivo o directorio y "número" es el número de inodo del archivo. Por lo tanto, un directorio raíz vacío se ve así, asumiendo que el inodo raíz es 0:

```pyth
[(., 0) (.., 0)]
```

Si agregamos un solo archivo "f" al directorio raíz, al que se le ha asignado el inodo número 1, el contenido del directorio raíz sería:

```pyth
[(., 0) (.., 0) (f, 1)]
```

Si un bloque de datos contiene datos de usuario, se muestra como un solo carácter dentro del bloque, por ejemplo, "h". Si está vacío y sin asignar, solo se muestran un par de corchetes vacíos  *([])*.

Por lo tanto, un sistema de archivos completo se representa de la siguiente manera:

```pyth
inode bitmap 11110000
inodes       [d a:0 r:6] [f a:1 r:1] [f a:-1 r:1] [d a:2 r:2] [] ...
data bitmap  11100000
data         [(.,0) (..,0) (y,1) (z,2) (f,3)] [u] [(.,3) (..,0)] [] ...
```



Este sistema de archivos tiene ocho inodos y ocho bloques de datos. 

El directorio raíz contiene tres entradas (distintas de "." y ".."), a "y", "z" y "f". Al buscar el inodo 1, podemos ver que "y" es un archivo normal (tipo f), con un solo bloque de datos asignado (dirección 1). En ese bloque de datos 1 están los contenidos del archivo "y": a saber, "u". También podemos ver que "z" es un archivo regular vacío (campo de dirección establecido en -1), y que "f" (número de inodo 3) es un directorio, también vacío. También puedes ver en los mapas de bits que las primeras cuatro entradas de mapa de bits de inodo están marcadas como asignadas, así como las tres primeras entradas de mapa de bits de datos.

El simulador se puede ejecutar con los siguientes indicadores:

```pyt
python vsfs.py -h
Usage: vsfs.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -i NUMINODES, --numInodes=NUMINODES 
                        number of inodes in file system
  -d NUMDATA, --numData=NUMDATA 
                        number of data blocks in file system
  -n NUMREQUESTS, --numRequests=NUMREQUESTS 
                        number of requests to simulate
  -r, --reverse         instead of printing state, print ops
  -p, --printFinal      print the final set of files/dirs
  -c, --compute         compute answers for me
```

Un uso típico simplemente especificaría una semilla aleatoria (para generar un problema diferente) y el número de solicitudes para simular. En este modo predeterminado, el simulador imprime el estado del sistema de archivos en cada paso y pregunta qué operación debe haber tenido lugar para llevar el sistema de archivos de un estado a otro. Por ejemplo:

```python
python vsfs.py -n 6 -s 16
...
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] []
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] []

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:2] [f a:-1 r:1] [] [] [] [] [] []
data bitmap   10000000
data          [(.,0) (..,0) (y,1)] [] [] [] [] [] [] []

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:2] [f a:1 r:1] [] [] [] [] [] []
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] []

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:2] [f a:1 r:2] [] [] [] [] [] []
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (m,1)] [u] [] [] [] [] [] []

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:2] [f a:1 r:1] [] [] [] [] [] []
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] []

Which operation took place?

inode bitmap  11100000
inodes        [d a:0 r:2] [f a:1 r:1] [f a:-1 r:1] [] [] [] [] []
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (z,2)] [u] [] [] [] [] [] []

Which operation took place?

inode bitmap  11110000
inodes        [d a:0 r:3] [f a:1 r:1] [f a:-1 r:1] [d a:2 r:2] [] [] [] []
data bitmap   11100000
data          [(.,0) (..,0) (y,1) (z,2) (f,3)] [u] [(.,3) (..,0)] [] [] [] [] []
```

Cuando se ejecuta en este modo, el simulador solo muestra una serie de estados y pregunta qué operaciones hicieron que ocurrieran estas transiciones. Ejecutar el indicador  "-c" nos muestra las respuestas. Específicamente, se creó el archivo "/y", se le agregó un bloque único, se creó un enlace duro de "/m" a "/ y", se eliminó "/m" mediante una llamada a unlink, se creó el archivo "/z" y el directorio "/f" creado:

```python
python vsfs.py -n 6 -s 16 -c
```

También puedes ejecutar el simulador en modo "inverso" (con la bandera "-r"), imprimiendo las operaciones en lugar de los estados para ver si puede predecir los cambios de estado de las operaciones dadas:

```python
python vsfs.py -n 6 -s 16 -r
```

Algunas otros indicadores controlan varios aspectos de la simulación, incluido el número de inodos ("-i"), el número de bloques de datos ("-d") y si se imprime la lista final de todos los directorios y archivos del archivo. sistema ("-p").

### Ejercicios

Utiliza esta herramienta, *vsfs.py*, para estudiar cómo cambia el estado del sistema de archivos a medida que se realizan diversas operaciones. El sistema de archivos comienza en un estado vacío, con solo un directorio raíz. A medida que se lleva a cabo la simulación, se realizan varias operaciones, cambiando así lentamente el estado en disco del sistema de archivos.

1. Ejecuta el simulador con algunas semillas aleatorias diferentes (digamos 17, 18, 19, 20) y indica  si puedes averiguar qué operaciones deben haber tenido lugar entre cada cambio de estado
2. Ahora haz lo mismo, usando diferentes semillas aleatorias (digamos 21, 22, 23, 24), excepto ejecutar con la bandera -r, lo que te hará adivinar el cambio de estado mientras se  muestra la operación. ¿Qué puedes concluir acerca de los algoritmos de asignación de inodos y bloques de datos, en términos de qué bloques se prefiere asignar?
3. Ahora reduzca el número de bloques de datos en el sistema de archivos, a números muy bajos (digamos dos), y ejecuta el simulador para un centenar de solicitudes. ¿Qué tipos de archivos terminan en el sistema de archivos con este diseño tan restringido? ¿Qué tipo de operaciones fallarían?
4. Ahora haga lo mismo, pero con inodos. Con muy pocos inodos, ¿qué tipos de operaciones pueden tener éxito? ¿Cuál suele fallar? ¿Cuál es el estado final probable del sistema de archivos?.
5. Considere un sistema de archivos en el que se puede eliminar un archivo y recuperar su espacio en disco mientras todavía existen enlaces a ese archivo. ¿Qué problemas pueden ocurrir si se crea un nuevo archivo en la misma área de almacenamiento o con el mismo nombre de ruta absoluta? ¿Cómo se pueden evitar estos problemas?
6. Si el sistema operativo supiera que una determinada aplicación va a acceder a los datos del archivo de forma secuencial, ¿cómo podría aprovechar esta información para mejorar el rendimiento?
7. Proporciona un ejemplo de una aplicación que podría beneficiarse del soporte del sistema operativo para el acceso aleatorio a archivos indexados.
8. Discute las ventajas y desventajas de soportar enlaces a archivos que cruzan puntos de montaje (es decir, el enlace del archivo se refiere a un archivo que está almacenado en un volumen diferente).
9. Algunos sistemas permiten compartir archivos manteniendo una sola copia de un archivo, otros sistemas mantienen varias copias, una para cada uno de los usuarios  que comparten el archivo. Discute los méritos relativos de cada enfoque.
10. Analiza las ventajas y desventajas de asociar con sistemas de archivos remotos (almacenados en servidores de archivos) un conjunto diferente de fallas  semánticas de este sistema archivos remotos con los sistemas de archivos locales. 

### HDD

En los ejercicios se utiliza tarea *disk.py* , programa que muestra  el funcionamiento de un disco duro moderno. Tiene muchas opciones diferentes y, a diferencia de la mayoría de las otras simulaciones, tiene un animador gráfico para mostrarle exactamente lo que sucede cuando el disco está en acción.

Primero hagamos un ejemplo simple. Para ejecutar el simulador y calcular algunos tiempos básicos de búsqueda, rotación y transferencia, primero debe proporcionar una lista de solicitudes al simulador. Esto se puede hacer especificando las solicitudes exactas o haciendo que el simulador genere algunas al azar.

Comenzaremos especificando una lista de solicitudes nosotros mismos. Primero hagamos una sola solicitud:

```bash
python disk.py -a 10
```

```python
REQUESTS [br '10']

For the requests above, compute the seek, rotate, and transfer times.
Use -c or the graphical mode (-G) to see the answers.
```

Para poder calcular los tiempos de búsqueda, rotación y transferencia para esta solicitud, debes conocer un poco más de información sobre el diseño de los sectores, la posición inicial del cabezal del disco, etc. Para ver gran parte de esta información, ejecute el simulador en modo gráfico (-G):

```bash
python disk.py -a 10 -G
```

En este punto, debería aparecer una ventana con nuestro disco simple. El cabezal del disco está colocada en la pista exterior, a la mitad del sector 6. Como puedes ver, el sector 10 (nuestro sector de ejemplo) está en la misma pista, aproximadamente un tercio de la vuelta. El sentido de giro es en sentido antihorario. Para ejecutar la simulación, presiona la tecla *s* mientras la ventana del simulador está resaltada.

Cuando se completa la simulación, deberías poder ver que el disco pasó 105 unidades de tiempo en rotación y 30 en transferencia para acceder al sector 10, sin tiempo de búsqueda. Presiona *q* para cerrar la ventana del simulador.

Para calcular esto (en lugar de simplemente ejecutar la simulación), necesitas conocer algunos detalles sobre el disco. Primero, la velocidad de rotación se establece de forma predeterminada en 1 grado por unidad de tiempo. Por lo tanto, para hacer una revolución completa, se necesitan 360 unidades de tiempo. En segundo lugar, la transferencia comienza y termina en el punto medio entre sectores. Así, para leer el sector 10, la transferencia comienza a mitad de camino entre 9 y 10, y termina a mitad de camino entre 10 y 11. Finalmente, en el disco predeterminado, hay 12 sectores por pista, lo que significa que cada sector ocupa 30 grados del espacio de rotación. Por lo tanto, para leer un sector, se necesitan 30 unidades de tiempo (dada nuestra velocidad de rotación predeterminada).

Con esta información en la mano, ahora deberías poder calcular los tiempos de búsqueda, rotación y transferencia para acceder al sector 10. Dado que el cabezal comienza en la misma pista que el sector 10, no hay tiempo de búsqueda. Debido a que el disco gira a 1 grado/unidad de tiempo, se necesitan 105 unidades de tiempo para llegar al comienzo del sector 10, a la mitad entre 9 y 10.  Finalmente,  transferir el sector toma 30 unidades de tiempo.

Ahora hagamos un ejemplo un poco más complejo:

```bash
python disk.py -a 10,11 -G
```

En este caso, estamos transfiriendo dos sectores, el 10 y el 11. ¿Cuánto tiempo llevará? 

Como probablemente adivinastes, esta simulación toma solo 30 unidades de tiempo más, para transferir el siguiente sector 11. Por lo tanto, los tiempos de búsqueda y rotación siguen siendo los mismos, pero el tiempo de transferencia para las solicitudes se duplica. De hecho, puedes ver estas sumas en la parte superior de la ventana del simulador. También se imprimen en la consola de la siguiente manera:

```python
...
Sector:  10  Seek:  0  Rotate:105  Transfer: 30  Total: 135
Sector:  11  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
TOTALS       Seek:  0  Rotate:105  Transfer: 60  Total: 165
```

Ahora hagamos un ejemplo con una búsqueda. Prueba el siguiente conjunto de solicitudes:

```bash
python disk.py -a 10,18 -G
```

Para calcular cuánto tiempo llevará esto, necesitas saber cuánto tiempo llevará una búsqueda. La distancia entre cada pista es por defecto de 40 unidades de distancia, y la tasa predeterminada de búsqueda es de 1 unidad de distancia por unidad de tiempo. Por tanto, una búsqueda desde la pista exterior a la pista media toma 40 unidades de tiempo.

También deberías conocer las políticas de planificación. El valor predeterminado es FIFO, por lo que, por ahora, puedes calcular los tiempos de solicitud asumiendo que el orden de procesamiento coincide con la lista especificada a través del indicador -a. 

Para calcular cuánto tiempo tardará el disco en atender estas solicitudes, primero calculamos cuánto tiempo tarda en acceder al sector 10, que sabemos que son 135 unidades de tiempo (105 en rotación, 30 en transferencia). Una vez que se completa esta solicitud, el disco comienza a buscar la pista intermedia donde se encuentra el sector 18, tomando 40 unidades de tiempo. Luego, el disco gira al sector 18 y lo transfiere durante 30 unidades de tiempo, completando así la simulación. Pero, ¿cuánto tiempo lleva esta rotación final?

Para calcular el retraso de rotación para 18, primero calcula cuánto tiempo tardaría el disco en girar desde el final del acceso al sector 10 hasta el comienzo del acceso al sector 18, asumiendo una búsqueda de costo cero. Como puedes ver en el simulador, el sector 10 en la vía exterior está alineado con el sector 22 en la vía central, y hay 7 sectores que separan 22 de 18 (23, 12, 13, 14, 15, 16 y 17, mientras el disco gira en sentido antihorario). Girar a través de 7 sectores toma 210 unidades de tiempo (30 por sector). Sin embargo, la primera parte de esta rotación se dedica a buscar la vía del medio, durante 40 unidades de tiempo. Por tanto, el retardo de rotación real para acceder al sector 18 es 210 menos 40, 170 unidades de tiempo. Ejecuta el simulador para comprobarlo tu mismo, ten en cuenta que puedes ejecutar sin gráficos y con la bandera "-c" para ver los resultados.

```bash
python disk.py -a 10,18 -c
...
Sector:  10  Seek:  0  Rotate:105  Transfer: 30  Total: 135
Sector:  18  Seek: 40  Rotate:170  Transfer: 30  Total: 240
TOTALS       Seek: 40  Rotate:275  Transfer: 60  Total: 375
```

### Ejercicios

1. Calcula los tiempos de búsqueda, rotación y transferencia para los siguientes conjuntos de solicitudes: `-a 0, -a 6, -a 30, -a 7,30,8` y finalmente `-a 10,11,12,13`.
2. Realiza las mismas solicitudes anteriores, pero cambia la tasa de búsqueda a valores diferentes: `-S 2, -S 4, -S 8, -S 10, -S 40, -S 0.1`. ¿Cómo cambian los tiempos?
3. Realiza las mismas solicitudes anteriores, pero cambia la velocidad de rotación: `-R 0.1, -R 0.5, -R 0.01`. ¿Cómo cambian los tiempos?
4. FIFO no siempre es lo mejor, por ejemplo, con el flujo de solicitudes `-a 7,30,8`, ¿en qué orden deben procesarse las solicitudes? Ejecuta el planificador *SSTF*  (*-p SSTF*) en esta carga de trabajo; ¿Cuánto tiempo debe tomar (búsqueda, rotación, transferencia) para que se atienda cada solicitud?
5. Ahora usa el planificador de tiempo de acceso más corto primero *(SATF) (-p SATF)*. ¿Hay alguna diferencia para  una carga de trabajo `-a 7,30,8`? Busca un conjunto de solicitudes en las que SATF supere a SSTF, ¿cuándo es mejor SATF que SSTF?.
6. Aquí hay una secuencia de solicitud para probar: `-a 10,11,12,13`. ¿Qué sale mal cuando se ejecuta? Intenta agregar un sesgo de pista para solucionar este problema (*-o skew*). Dada la tasa de búsqueda predeterminada, ¿cuál debería ser el sesgo para maximizar el rendimiento? ¿Qué pasa con las diferentes tasas de búsqueda (por ejemplo, `-S 2, -S 4`)? En general, ¿podrías escribir una fórmula para calcular el sesgo?.