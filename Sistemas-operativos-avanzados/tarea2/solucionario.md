# Respuesta 1

Hay variedades porque tener opciones al momento de programar es positivo y puede facilitar el trabajo. 
Pasar el _environment_ y el _path_ pueden ser muy útiles cuando no se conoce bien el tipo de shell en el 
que el programa escrito va a interpretarse.
Sin embargo, desde mi punto de vista, la forma más ideal de pasar los argumentos es a través de un 
solo puntero que los contenga todos, de la misma forma en que siempre se hace con el puntero que 
contiene la información del _environment_, aunque los comandos `execlp`, `execl`, `execle` sean 
útiles cuando no hay necesidad de pasar muchos argumentos.

## Nota importante
Al ejecutar este programa...
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    pid_t p = fork();

    if (p == 0) {
        //char * myargs[];
        //execl("/bin/ls", "superls", "-la", (char *) NULL);
        execlp("ls", "superls", "-lah", (char *) NULL);
        fprintf(stdout, "Hello, friend.\n");
        execl("/bin/ls", "superls", "-la", (char *) NULL);

    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);

        w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
} 
```

obtenemos la siguietne salida :
```bash
gwynplaine@tabernacle:~/Documentos/univir/soa/tarea2$ ./a.out 
total 32K
drwxrwxr-x 2 gwynplaine gwynplaine 4,0K jun 18 15:53 .
drwxr-xr-x 6 gwynplaine gwynplaine 4,0K jun 18 14:50 ..
-rwxrwxr-x 1 gwynplaine gwynplaine 8,5K jun 18 15:53 a.out
-rw-rw-r-- 1 gwynplaine gwynplaine 1000 jun 18 15:52 solucion1.c
-rw-rw-r-- 1 gwynplaine gwynplaine 1,8K jun 18 15:50 solucion1.mkd
-rw-rw-r-- 1 gwynplaine gwynplaine 2,4K jun 18 15:27 Tarea2-codificacion-CC571.mkd
[11538]: 11539 just terminated!
[11538]: got code -1. Process not found!
```

Note que, la última línea nos indica que nunca se ejecutó el comando `execl("/bin/ls", "superls", "-la", (char *) NULL);`, ni siquiera pudimos ejecutar el `fprintf(stdout, "Hello, friend.\n");`. Esto ocurre porque `exec()` cambió toda la imagen del proceso del hijo por la de `ls`. Ahora bien, para ejecutar todo, debemos realizar un `fork()` a la vez o realizarlo dentro del hijo.


# Respuesta 2

Tanto el proceso padre como el proceso hijo pueden escribir en el descriptor del fichero 
creado puesto que el hijo tiene una copia de la memoria.
Al escribir sobre el, si omitimos el hecho de que no podemos determinar cuál proceso comenzará 
a escribir primero sobre el descriptor, no ocurre ningún problema... verdad?
Al menos no con el siguiente código:

```c
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
    char * filename = "output2.out";
    int fd = open(
        filename,
        O_WRONLY | O_CREAT | O_APPEND,
        S_IRWXU | S_ISUID | S_IRWXG | S_ISGID
    );
    fprintf(stdout, "[%d]: file descriptor id = %d\n", getpid(), fd);

    if (fd == -1)  {
        fprintf(stderr, "[%d]: cannot open file descriptor.\n", getpid());
        exit(EXIT_FAILURE);
    } else {
        pid_t p = fork();

        if (p == 0) {
            dprintf(fd, "[%d]: I'm the child.\n", getpid());
        } else if (p > 0) {
            dprintf(fd, "[%d]: I'm the father.\n", getpid());
        } else {
            fprintf(stderr, "[%d]: fork failed!\n", getpid());
        }
    }
    

    return 0;
}
```


Pero intentemos otra cosa:


```c
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void superwriter(int fd, const char * s) {
    int i;

    for (i = 0; i < 100; i++)
        dprintf(fd, s);
    
}

int main(int argc, char * argv[]) {
    char * filename = "output2.out";
    int fd = open(
        filename,
        O_WRONLY | O_CREAT | O_APPEND,
        S_IRWXU | S_ISUID | S_IRWXG | S_ISGID
    );
    fprintf(stdout, "[%d]: file descriptor id = %d\n", getpid(), fd);

    if (fd == -1)  {
        fprintf(stderr, "[%d]: cannot open file descriptor.\n", getpid());
        exit(EXIT_FAILURE);
    } else {
        pid_t p = fork();

        if (p == 0) {
            dprintf(fd, "[%d]: I'm the child.\n", getpid());
            superwriter(fd, "child!");
        } else if (p > 0) {
            dprintf(fd, "[%d]: I'm the father.\n", getpid());
            superwriter(fd, "father!");
        } else {
            fprintf(stderr, "[%d]: fork failed!\n", getpid());
        }
    }
    

    return 0;
}

```



La salida en el fichero es esta:
```bash
gwynplaine@tabernacle:~/Documentos/univir/soa/tarea2$ cat output2.out 
[20903]: I'm the father.
father![20904]: I'm the child.
father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!father!child!child!
```

Se puede observar, claramente, que existe una _condición de carrera_. Tanto padre como hijo escriben intermitentemente. No se puede determinar quién escribirá primero y además, no se puede asegurar que 
uno empiece la operación antes que otro lo haga. Esto se soluciona con una llamada a `wait()`.


# Respuesta 3

Dado que el proceso hijo ha cerrado el descriptor de salida estándar, este no podrá ejecutar 
`printf` porque este escribe sobre el descriptor de salida estándar. Sin embargo, cerrar este 
descriptor en el hijo no afecta al padre puesto que el hijo hereda una copia de los descriptores 
abiertos en el padre. Así, lo que el hijo haga afecta a la copia de sus descriptores.

## Nota importantes
Debemos hacer una importante acotación entre la diferencia entre el _descriptor_ y la 
_la descripción del fichero abierto_. Puede haber muchos descriptores apuntando a la misma 
_descripción_. Recordemos que, en linux, **todo es un fichero**, incluídos dispositivos de 
entrada y salida. Así, un mismo _dispositivo_ puede ser referenciado por más de un descriptor. 
Cada proceso tiene su propia tabla de descriptores y puede modificarla sin afectar a las descripciones 
a las que referencian, ni a los descriptores de otros procesos.
Algunas descripciones de ficheros abiertos apuntan no ha dispositivos, ficheros ejecutables, interfaces, 
sockets, o puertos, sino que apuntan a sectores de discos donde se almacenan los datos. Es decir, 
apuntan a los directorios. Estos almacenan información acerca del directorio padre, su contenido, otros 
directorios, ficheros, etc ...