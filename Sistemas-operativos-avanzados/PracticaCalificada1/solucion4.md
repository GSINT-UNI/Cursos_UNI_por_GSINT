# Solución 4

## Explicando los resultados

```
gwynplaine@tabernacle:~/Documentos/univir/soa/Practica-Calificada1-CC571$ ./F1
El tiempo promedio de  syscall es 813.450867 nano-segundos.
```
Lo que este programa hace es computar un promedio de lo que toma una  
llamada a `read` en nanosegundos. El promedio se hace tomando 10^6 muestras 
Interpreta la llamada en particular como el tiempo que le toma al  computador 
realizar una llamada al sistema.
```
gwynplaine@tabernacle:~/Documentos/univir/soa/Practica-Calificada1-CC571$ ./F2
100 El tiempo de read() toma  263487 ns,en promedio 2634 ns/read() 
1000 El tiempo de read() toma  2582016 ns,en promedio 2582 ns/read() 
10000 El tiempo de read() toma  14461926 ns,en promedio 1446 ns/read() 
100000 El tiempo de read() toma  78704940 ns,en promedio 787 ns/read() 
1000000 El tiempo de read() toma  787972137 ns,en promedio 787 ns/read() 
```
Lo que hace este programa medir el timepo que toman 100, 1000, 10000, 100000 
y 1000000 llamadas a `read` en nanosegundos y computar el promedio de lo que 
toma una llamada en cada caso. Es curioso observar que el tiempo promedio que 
toma cada llamada disminuye a medida que avanza el número de llamadas.
```
gwynplaine@tabernacle:~/Documentos/univir/soa/Practica-Calificada1-CC571$ ./F3
Llamada al sistema: 0.538292 microsegundos

Cambio de contexto en : 2.495735 microsegundos
gwynplaine@tabernacle:~/Documentos/univir/soa/Practica-Calificada1-CC571$ 
```
Este es el programa más interesante de los tres. Calcula, desde el padre, el 
tiempo que se tarda la comunicación entre él y su hijo a través de una 
tubería. Luego de eso, calcula el promedio en microsegundos, todo en una línea.
El programa usa `sched_setaffinity` para forzar al hijo y al padre a correr 
en la misma CPU. El programa interpreta este tiempo como el cambio de contexto.

##  Diferencias entre `CLOCK_BOOTTIME` y `CLOCK_REALTIME`
+ `CLOCK_BOOTTIME`, especifica a `clock_gettime` que debe tomar el tiempo 
respecto al tiempo en que se inició el sistema. Cuenta el tiempo que el 
ordenador ha pasado suspendido. 
+ `CLOCK_REALTIME`, especifica a `clock_gettime` que debe tomar el tiempo 
respecto a la primera fecha que puede computar el sistema.
+ `clock_gettime` está obsoleto. `gettimeofday` toma el tiempo al momento 
del retorno, tiene en cuenta la zona horaria. Es decir, muestra la 'hora' 
a la que se encuentra el usuario.