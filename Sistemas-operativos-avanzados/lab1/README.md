# Laboratorio de clase CC-571

Código a ser resuelto dentro de la clase. 

1 .Explica el funcionamiento de *fork()* en los siguientes códigos:

```c
             #include  <stdio.h>
             #include  <string.h>
             #include  <sys/types.h>

             #define   MAX_CONTEO  200
            #define   TAM_BUFFER   100

            void  main(void)
            {
              pid_t  pid;
              int    i;
              char   buf[TAM_BUFFER];

              fork();
              pid = getpid();
              for (i = 1; i <= MAX_CONTEO; i++) {
              sprintf(buf, "Esta linea es de pid %d, valor = %d\n", pid, i);
              write(1, buf, strlen(buf));
         } 
        }
```
 y 
    
```c

           #include  <stdio.h>
          #include  <sys/types.h>
    
          #define   MAX_CONTEO  200
    
          void  ProcesoHijo(void);      
          void  ProcesoPadre(void); 

          void  main(void)
          {
           pid_t  pid;
           pid = fork();
           if (pid == 0)
            ProcesoHijo();
           else
            ProcesoPadre();
          }

          void  ProcesoHijo(void)
          {
          int   i;

          for (i = 1; i <= MAX_CONTEO; i++)
            printf("Esta linea es del hijo, valor = %d\n", i);
            printf("El proceso hijo esta completo\n");
            }

         void  ProcesoPadre(void)
         {
         int   i;

         for (i = 1; i <= MAX_CONTEO; i++)
          printf("Esta linea es el de padre, valor = %d\n", i);
         printf("El proceso padre esta hecho\n");
        }
```

2 . Escribe un programa que llame a *fork()*. Antes de llamar a *fork()*, indica que el proceso principal acceda a una variable (por ejemplo, x) y establezca su valor en algo (por ejemplo, 50). ¿Qué valor es la variable en el proceso hijo? ¿Qué le sucede a la variable cuando tanto el hijo como el padre cambian el valor de x?


3 . Escribe otro programa usando *fork()*. El proceso hijo debe imprimir "Hola CC-571"; el proceso padre debe imprimir "a cuidarse". Debes intentar asegurarse de que el proceso hijo siempre imprima primero; ¿Puedes hacer esto sin llamar a *wait()* en el proceso padre?.

4 . Ahora escribe un programa que use *wait()* para esperar a que el proceso hijo termine en el padre. ¿Qué devuelve *wait()*? , ¿qué sucede si se usa *wait()* en el hijo?.

5 . Escribe una ligera modificación del programa anterior, esta vez usando *waitpid()* en lugar de *wait()*. ¿Cuándo sería útil *waitpid()*?.

6 . En  este ejercicio, mediremos los costos de una llamada al sistema. Medir el costo de una llamada al sistema es relativamente fácil. Por ejemplo, puedes llamar repetidamente a una llamada simple del sistema (por ejemplo, realizar una lectura de 0 bytes) y determinar el tiempo que tarda; dividir el tiempo por el número de iteraciones le da una estimación del costo de una llamada al sistema.

Una cosa que tendrá que tener en cuenta es la precisión y exactitud de su temporizador. La llamada al sistema `clock_gettime` es el  sucesor `gettimeofday` temporizador típico  con algunos cambios clave: mayor precisión y la capacidad de solicitar relojes específicos. Escribe un programa en C, para una aplicación de lectura (*read*).


## Nota del autor del solucionario
Las respuestas presentadas para este laboratorio son respuestas no oficiales. 