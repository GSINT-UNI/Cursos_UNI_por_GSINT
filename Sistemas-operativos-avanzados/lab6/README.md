# Notas del laboratorio 6 CC-571

En estas notas, veremos los siguientes temas:

* Introducción a la concurrencia
* Threads API
* Locks
* Variables de condición 
* Semáforos
* Problemas de concurrencia comunes

### Observaciones

* Todo el código fuente es parte del libro:  Operating Systems: Three Easy Pieces  de Remzi H. Arpaci-Dusseau y Andrea C. Arpaci-Dusseau, alojado en  [https://github.com/remzi-arpacidusseau/ostep-code](https://github.com/remzi-arpacidusseau/ostep-code). 
* Se usa el código con fines didácticos.
* Se realizará la solución en pares de alumnos.

#### Ejercicios de concurrencia

Se utiliza el programa, `x86.py`, que permite ver cómo las diferentes interrelaciones de hilos causan o evitan condiciones de carrera. Carpeta *concurrency*.

1. Examinemos un programa simple, *loop.s*. Ejecuta el programa con estos argumentos `( python x86.py -p loop.s -t 1 -i 100 -R dx)` Esto especifica un solo hilo, una interrupción cada 100 instrucciones y el rastreo del registro `% dx`. ¿Qué será `%dx` durante la ejecución? Usa el indicador  `-c` para verificar sus respuestas.
2. Usemos el mismo código, diferentes indicadores: `( python x86.py -p loop.s -t 2 -i 100 -a dx = 3, dx = 3 -R dx)`.  Esto especifica dos hilos e inicializa cada `%dx` a `3`. ¿Qué  valores  verá `% dx`? Ejecuta el indicacor  `-c` para comprobar. ¿La presencia de varios hilos afecta los cálculos?. ¿Hay una carrera en este código?.
3. Ejecuta esto:  `python x86.py -p loop.s -t 2 -i 3 -r -a dx = 3, dx = 3 -R dx`.  Esto hace que el intervalo de interrupción sea pequeño/aleatorio. Usa diferentes semillas `(-s)` para ver diferentes intercalaciones. ¿Cambia algo la frecuencia de interrupción?.
4. Ahora, un programa diferente, `looping-race-nolock.s`, que accede a una variable compartida ubicada en la dirección `2000`. Llamaremos a esta variable *value*. Ejecuta con un solo hilo para confirmar su comprensión: `python x86.py -p looping-race-nolock.s -t 1 -M 2000`. ¿Cuál es el valor (es decir, en la dirección de memoria 2000) durante la ejecución?.  Usa `-c` para verificar.
5. Ejecuta con múltiples iteraciones/hilos:` python x86.py -p looping-race-nolock.s -t 2 -a bx = 3 -M 2000 `. ¿Por qué cada hilo se repite tres veces? ¿Qué es el valor final del `value`?.
6. Ejecuta con intervalos de interrupción aleatorios:  `python x86.py -p looping-race-nolock.s
   -t 2 -M 2000 -i 4 -r -s 0` con diferentes semillas `(-s 1, -s 2`, etc.). ¿Cuál es el valor final de `value`?.  ¿Importa el momento de la interrupción?.  ¿Dónde está exactamente la sección crítica?.
7. Ahora examina los intervalos de interrupción fijos: `python x86.py -p looping-race-nolock.s -a bx = 1 -t 2 -M 2000 -i 1`.  ¿Cuál será el valor final  de la variable compartida `value`? ¿Qué pasa cuando cambia `-i 2, -i 3`, etc.? ¿Para qué intervalos de interrupción el programa da la respuesta "correcta"?
8. Ejecuta lo mismo para más bucles. ¿Qué intervalos de interrupción `(-i)` conducen a un resultado correcto? ¿Qué intervalos son sorprendentes?.
9.  Ejecuta:  `python x86.py -p wait-for-me.s -a ax = 1, ax = 0 -R ax -M 2000`. Explica el resultado. ¿Cómo debería comportarse el código?. ¿Cómo utilizan los hilos el valor en la ubicación 2000? ¿Cuál será su valor final?.
10. Cambia las entrada y ejecuta `python x86.py -p wait-for-me.s -a ax = 0, ax = 1 -R ax -M 2000`- ¿Cómo se comportan los hilos? ¿Qué está haciendo el hilo `0`? ¿Cómo cambiaría el resultado de la traza cambiar el intervalo de interrupción ?. ¿El programa utiliza la CPU de manera eficiente?.

#### Ejercicios  sobre threads API

En esta sección, se realizan algunos programas sencillos de varios hilos y usamos una herramienta específica, llamada helgrind, para encontrar problemas en estos programas. Carpeta: *threats-api*.

1. Primero compila `main-race.c`. Examina el código para que puedas ver la carrera de datos en el código. Ahora ejecuta helgrind (escribiendo `valgrind --tool = helgrind main-race`) para ver cómo informa de la carrera. ¿Apunta a las líneas correctas de código? ¿Qué otra información te da?. ¿Qué sucede cuando elimina una de las líneas de código infractoras?
2. Veamos el siguiente programa `main-deadlock.c`. Examina el código. Este código tiene un problema conocido como deadlock. ¿Puedes ver qué problema podría tener? . Ahora ejecuta `helgrind` en este código. ¿Qué informa `helgrind`?.
3. Ahora ejecuta `helgrind` en `main-deadlock-global.c`. Examina el código:  ¿tiene el mismo problema que main-deadlock.c? ¿Debería helgrind informar el mismo error? ¿Qué te dice esto sobre herramientas como helgrind?.
4. Veamos ahora `main-signal.c`. Este código usa una variable (`done`) para señalar que un proceso hijo ha terminado y que un proceso padre ahora puede continuar. ¿Por qué este código es ineficaz? Ahora ejecuta helgrind en este programa. ¿Qué informa? ¿Es correcto el código?.
5. Ahora estudia  una versión ligeramente modificada del código, que se encuentra en `main-signal-cv.c`. Esta versión utiliza una variable de condición para realizar la señalización. ¿Por qué se prefiere este código a la versión anterior? ¿Es la corrección, el rendimiento o ambos? Una vez más, ejecuta `helgrind` en `main-signal-cv`. ¿Informa algún error?. 

#### Ejercicios de locks

Se utiliza el programa, `x86.py`, que permite ver cómo las diferentes interrelaciones de hilos causan o evitan condiciones de carrera. Carpeta *locks*.

1. Examinar `flag.s`. Este código implementa el bloqueo con un solo indicador de memoria. ¿Puedes entender el ensamblador?.
2. Cuando se ejecuta con los valores predeterminados, ¿funciona `flag.s`? Utiliza los indicadores -M y -R para rastrear variables y registros (y active -c para ver sus valores). 
3. Cambia el valor del registro `%bx` con la indicador  `-a` (por ejemplo, `-a bx = 2, bx = 2` si está ejecutando solo dos hilos). ¿Qué hace el código? ¿Cómo cambia su respuesta a la pregunta anterior
4. Establezca `bx` en un valor alto para cada hilo y luego usa el indicador `-i` para generar diferentes frecuencias de interrupción. ¿Qué valores conducen a malos resultados?.  ¿Qué valores conducen a buenos resultados?.
5. Ahora veamos el programa `test-and-set.s`. Primero, intenta comprender el código, que usa la instrucción `xchg` para construir una primitiva de bloqueo simple. ¿Cómo se escribe la adquisición de bloqueo? .
6. Ahora ejecuta el código, cambiando el valor del intervalo de interrupción `(-i)` nuevamente y asegurándose de repetir varias veces. ¿El código siempre funciona como se esperaba? ¿A veces conduce a un uso ineficiente de la CPU? ¿Cómo puedes cuantificar eso?.
7. Utiliza el indicador `-P` para generar pruebas específicas del código de bloqueo. Por ejemplo, ejecuta una planificación que tiene el bloqueo en el primer hilo,  luego intenta adquirirlo en el segundo. ¿Sucede lo correcto? ¿Qué más debería probar?.
8. Ahora veamos el código en `peterson.s`, que implementa el algoritmo de Peterson . Estudia el código.
9. Ahora ejecuta el código con diferentes valores de `-i`. ¿Qué tipo de comportamiento diferente ves? Asegúrese de configurar los ID de hilo de manera adecuada (usando `-a bx = 0, bx = 1` por ejemplo) como lo asume el código.
10. ¿Puede controlar la planificación (con el indicador `-P`) para probar que el código funciona? ¿Cuáles son los diferentes casos que debes mostrar? Piensa en la exclusión mutua y evita el deadlock.
11. Ahora estudia el código de  `ticket.s`. Ejecuta con los siguientes indicadores: `-a bx = 1000, bx = 1000`(lo que hace que cada hilo pase por la sección crítica 1000 veces). Observa lo que pasa. ¿Los hilos pasan mucho tiempo esperando el bloqueo?. ¿Cómo se comporta el código a medida que agrega más hilos?.
12. Ahora examina `yield.s`, en el que una instrucción de rendimiento permite que un hilo ceda el control de la CPU. Encuentra un escenario donde `test-and-set.s` desperdicia ciclos girando, pero `yield.s` no. ¿Cuántas instrucciones se guardan? ¿En qué escenarios surgen estos ahorros?
13. Por último, examina `test-and-test-and-set.s`. ¿Qué hace este lock? ¿Qué tipo de ahorro introduce en comparación con `el test-and-set.s`?.

#### Ejercicios de variables de condición

Estos ejercicios te permiten explorar código real que usa bloqueos y variables de condición para implementar varias formas del poblema productor/consumidor. Además se ejecutarán evarias configuraciones para aprender qué funciona y qué no, así como otras complejidades. Carpeta: *cv*.

1. Sea  `main-two-cvs-while.c`. Estudia el código. ¿Crees que comprende lo que debería suceder cuando ejecuta el programa?
2. Ejecuta con un productor y un consumidor, y haga que el productor produzca algunos valores. Comienza con un búfer (tamaño 1) y luego auméntelo. ¿Cómo cambia el comportamiento del código con búferes más grandes? . ¿Qué predeciría `num_full` con diferentes tamaños de búfer (por ejemplo: `-m 10`) y diferentes números de elementos producidos (por  ejemplo `-l 100`).
3. Veamos algunos tiempos. ¿Cuánto tiempo cree que llevará la siguiente ejecución, con un productor, tres consumidores, un búfer compartido de entrada única y cada consumidor haciendo una pausa en el punto `c3` durante un segundo? `./main-two-cvs- while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0: 0,0,0,1,0,0,0: 0, 0,0,1,0,0,0 -l 10 -v -t`. Ahora cambie el tamaño del búfer compartido a `3 (-m 3`). ¿Hará esto alguna diferencia en el tiempo total?.
4. Explica el siguiente resultado : ¿a qué hora se predice en este caso? `./main-two-cvs- while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1: 0,0,0,0,0,0,1: 0, 0,0,0,0,0,1 -l 10 -v -t`. Finalmente, cambia el tamaño del búfer a `3` nuevamente (`-m 3`). ¿En que tiempo se predice ahora?.
5. Ahora veamos `main-one-cv-while.c`. ¿Puedes configurar una cadena de suspensión, asumiendo un solo productor, un consumidor y un búfer de tamaño `1`, para causar un problema con este código Ahora cambia el número de consumidores a dos. ¿Puedes construir cadenas de suspensión para el productor y los consumidores a fin de causar un problema en el código?
6. Ahora examina `main-two-cvs-if.c`. ¿Puedes causar un problema en este código? Considera nuevamente el caso en el que solo hay un consumidor y luego el caso en el que hay más de uno.
7. Examina `main-two-cvs-while-extra-unlock.c`. ¿Qué problema surge cuando sueltas el bloqueo antes de hacer un put o un get? ¿Puedes causar de manera confiable que ocurra tal problema, dado una cadena de suspensión?. ¿Qué cosa mala puede pasar?.

#### Ejercicios de semáforos

En esta tarea, usaremos semáforos para resolver algunos problemas de concurrencia bien conocidos. Muchos de estos están tomados del libro  de Downey: Little Book of Semaphores, que hace un buen trabajo al reunir una serie de problemas clásicos.

Cada una de las siguientes preguntas proporciona un esqueleto de código; su trabajo es completar el código para que funcione dado los semáforos. En Linux, utilizará semáforos nativos; en una Mac (donde no hay soporte de semáforo), primero tendrá que construir una implementación (usando bloqueos y variables de condición). Carpeta *semaphores*.

1. El primer problema es simplemente implementar y probar una solución al problema de fork/join. Consulta *fork-join.c* para obtener más detalles. Agrega la llamada *sleep(1)* al proceso hijo para asegurarse de que esté funcionando.
2. Ahora generalicemos esto un poco investigando el problema llamado **rendezvous**. El problema es el siguiente: tiene dos hilos, cada uno de los cuales está a punto de ingresar a un punto llamado *rendezvouz* en el código. Ninguno de los dos debe salir de esta parte del código antes de que el otro ingrese. Considera utilizar dos semáforos para esta tarea y consulta *rendezvous.c* para obtener más detalles.
3. Ahora vamos un paso más allá implementando una solución general para la sincronización de barreras. Supongamos que hay dos puntos en una pieza secuencial de código, llamados $P_1$ y $P_2$. Poner una barrera entre $P_1$ y $P_2$ que garantiza que todos los hilos ejecutarán $P_1$ antes de que cualquier hilo ejecute $P_2$. Tu tarea es escribir el código para implementar una función de *barrier()* que se pueda usar de esta manera. Es seguro asumir que conoce N (el número total de hilos en el programa en ejecución) y que todos los N hilos intentarán entrar en la barrera.  Consulta *barrer.c* para obtener más detalles
4. Resolvamos el problema del lector-escritor. En esta primera variante, no te preocupes por el starvation. Consulta el código *reader-writer.c* para obtener más detalles. Agrega llamadas *sleep()* a tu código para demostrar que funciona como espera. ¿Puedes demostrar la existencia del problema de starvation?
5. Veamos de nuevo el problema del lector-escritor, pero esta vez considerando el starvation. ¿Cómo puede asegurarse de que todos los lectores y escritores eventualmente progresen? Consulta *reader-writer-nostarve.c* para obtener más detalles.
6. Utiliza semáforos para construir un mutex sin starvation, en el que cualquier hilo que intente adquirir el mutex eventualmente lo obtendrá. Consulta el código *mutex-nostarve.c* para obtener más información.

#### Ejercicios sobre problemas de concurrencia

Esta tarea te permite explorar un código real que  produce deadlock (o evita deadlock). Las diferentes versiones de código corresponden a diferentes enfoques para evitar el deadlock en una rutina simplificada `vector_add().` Carpeta *threads-bugs*.

1. Estudia el código de *vector-deadlock.c*, así como de *main-common.c*  y archivos relacionados. Ahora, ejecuta  *vector-deadlock.c* con los paramétros *-n 2 -l 1 -v*, que instancia dos hilos *(-n 2)*, cada uno de los cuales agrega un vector *(-l 1)*, y lo hace en modo detallado *(-v)* .  ¿Cómo cambia la salida de una ejecución a otra?
2. Ahora agregue el indicador *-d* y cambia el número de bucles *(-l)* de 1 a números más altos. ¿Qué pasa? ¿El código (siempre) produce deadlock?
3. ¿Cómo cambia el número de hilos *(-n)* el resultado del programa? ¿Hay valores de *-n* que aseguren que no se produzca un interbloqueo?
4. Ahora examina el código en *vector-global-order.c*.  ¿Por qué el código evita el deadlock? Además, ¿por qué hay un caso especial en esta rutina *vector-global-order()*, cuando los vectores de origen y destino son los mismos?
5. Ahora ejecuta el código con los siguientes indicadores: *-t -n 2 -l 100000 -d*. ¿Cuánto tiempo tarda en completarse el código? ¿Cómo cambia el tiempo total cuando aumenta el número de bucles o el número de hilos?
6. ¿Qué sucede si activa el indicador de paralelismo (-p)? ¿Cuánto esperaría que cambiara el rendimiento cuando cada hilo está trabajando para agregar diferentes vectores (que es lo que habilita -p) vs. en trabajar en los mismos?
7. Ahora estudiemos *vector-try-wait.c*.  ¿Es realmente necesaria la primera llamada a *pthread_mutex_trylock ()*?. ¿Qué tan rápido se ejecuta en comparación con el enfoque de orden global? ¿Cómo cambia el número de reintentos, contados por el código, a medida que aumenta el número de hilos?
8. Ahora veamos *vector-avoid-hold-and-wait.c*. ¿Cuál es el principal problema con este enfoque? ¿Cómo se compara su rendimiento con las otras versiones, cuando se ejecuta tanto con *-p* como sin él
9. Veamos *vector-nolock.c*. Esta versión no usa boqueos en absoluto. ¿Proporciona exactamente la misma semántica que las otras versiones? ¿Por qué o por qué no?
10. Ahora compara su rendimiento con las otras versiones, tanto cuando los hilos están trabajando en los mismos dos vectores , como cuando cada hilo está funcionando en vectores separados . ¿Cómo funciona esta versión sin bloqueo?


## Nota del autor del solucionario
El solucionario de este laboratorio no es oficial y está terriblemente incompleto.
