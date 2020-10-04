# Tarea de codificación 2 CC-571

### Normas

* Presentar cada una de sus respuestas en un archivo separado.
* Los archivos separados tendran el nombre de `solución1.c` o `solución2.mkd` si es que es la respuesta es texto.
* Las respuestas de texto deben tener más 300 palabras. No se aceptarán respuestas de menos palabras.
* La entrega es en un archivo comprimido. 
* No se admiten copias. **Cualquier evidencia de copia de otra fuente no serán consideradas y el puntaje será cero**. Escribe tus propias respuestas.


1 .Escribe un programa que llame a *fork()* y luego llame a alguna forma de *exec()* para ejecutar el programa `/bin/ls`. Prueba todas las variantes de `exec()`, incluidas (en Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()` y `execvpe()`. ¿Por qué crees que hay tantas variantes de la misma llamada básica?

2 . Escribe un programa que abre un archivo (con la llamada al sistema *open()*) y luego llame a *fork()* para crear un nuevo proceso. ¿Pueden el proceso hijo y el padre acceder al descriptor de archivo devuelto por *open()*?. ¿Qué sucede cuando escriben en el archivo simultáneamente, es decir, al mismo tiempo?

3 . Escribe un programa que cree un proceso hijo y luego, en el proceso hijo, cierre la salida estándar (*STDOUT FILENO*). ¿Qué sucede si el proceso hijo llama a *printf ()* para imprimir alguna salida después de cerrar el descriptor.

4 . En  este ejercicio, mediremos los costos de un cambio de contexto. Medir el costo de un cambio de contexto puede tener algunas complicaciones. El benchmark de [lmbench](http://www.bitmover.com/lmbench/) lo hace ejecutando dos procesos en una sola CPU y configurando dos pipeline UNIX entre ellos. Un pipeline es solo una de las muchas formas en que los procesos en un sistema UNIX pueden comunicarse entre sí. *lmbench* puede hacer una buena estimación del costo de un cambio de contexto. Puedes intentar recrear algo similar aquí, utilizando pipelines, o quizás algunos otro mecanismo de comunicación como los sockets UNIX.

Puedes utilizar, un temporizador típico como `gettimeofday()`. Si lees la página del manual verás allí que `gettimeofday()` devuelve el tiempo en microsegundos desde 1970; sin embargo, esto no significa que el temporizador sea preciso al microsegundo.

Puedes revisar para más información: [https://github.com/gz/contextswitch](https://github.com/gz/contextswitch).



## Nota del autor del solucionario:

Las respuestas del solucionario no son oficiales. 