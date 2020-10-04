# Notas del laboratorio 2 CC-571

En estas notas, veremos los siguientes temas:

* Introducción a la planificación
* La cola de retroalimentación de varios niveles (MLFQ)
* Cuota proporcional y loteria
* Planificación en un multiprocesador

## Introducción a la planificación

El programa, planificador.py, permite ver cómo se desempeñan los diferentes planificadores bajo métricas como el tiempo de entrega (TAT), el tiempo de respuesta y el tiempo de espera total. Se implementan tres planificadores: FIFO, SJF y RR.

Hay dos pasos para ejecutar el programa.

Primero, se ejecuta sin el indicador *-c*, que muestra qué problema resolver sin revelar las respuestas. Por ejemplo, si deseas calcular el TAT , el tiempo de respuesta y de espera para 3 trabajos con la política FIFO, se ejecuta:

```
  python planificador.py -p FIFO -j 3 -s 100
```

Esto especifica la política FIFO con tres trabajos y una semilla aleatoria de 100.

En este ejemplo, se generan tres trabajos. Como indica el programa, podemos usar las indicaciones para calcular algunas estadísticas y manejar mejor los conceptos.

Se puede usar el mismo programa para "resolver" el problema y ver si funciona correctamente. Para hacerlo, usa el flag `-c`.

```
  python planificador.py -p FIFO -j 3 -s 100 -c
```

Otro indicador útil es "-l", que le permite especificar los trabajos exactos que deseas planificar. Por ejemplo, si desea averiguar cómo se desempeñaría SJF con tres trabajos de longitud 5, 10 y 15, puedes ejecutar:

```
  python planificador.py -p SJF -l 5,10,15
```


Y luego puedes usar `-c` para resolverlo nuevamente. Ten en cuenta que cuando especifica los trabajos exactos, no es necesario especificar una semilla aleatoria o el número de trabajos: las longitudes de los trabajos se toman de su lista separada por comas.

Por supuesto, suceden cosas más interesantes cuando utiliza planificadores SJF o incluso RR (round robin).

### Recuerda que ..

Siempre puedes correr para guiarte por las opciones del programa.

```
  python planificador.py --help
```

### Ejercicios

1. Calcule el tiempo de respuesta y el TAT al ejecutar tres trabajos de longitud 200 con los planificadores SJF y FIFO.

1. Realiza la misma tarea pero con trabajos de diferentes longitudes: 100, 200 y 300.

1. Realiza la misma tarea pero también con el planificador RR y un segmento de tiempo de 1.

1. ¿Para qué tipos de cargas de trabajo SJF ofrece el mismo TAT que FIFO?

1. ¿Para qué tipos de cargas de trabajo y longitudes de cuantas, SJF ofrece los mismos tiempos de respuesta que RR?

1. ¿Qué sucede con el tiempo de respuesta con SJF a medida que aumenta la duración del trabajo? ¿Puedes usar el simulador para demostrar la tendencia?

1. ¿Qué sucede con el tiempo de respuesta con RR a medida que aumentan las longitudes de cuantas? ¿Puedes escribir una ecuación que dé el peor tiempo de respuesta, dados N trabajos?.

## MLFQ

Este programa, mlfq.py, te permite ver cómo el planificador MLFQ, presentado en clase. Se puede usar esto para generar problemas, usando semillas aleatorias, o usarlo para construir un experimento cuidadosamente diseñado para ver cómo funciona MLFQ en diferentes circunstancias. Para ejecutar el programa, escribe:

```
  python mlfq.py
```

Utiliza el flag de ayuda (-h) para ver opciones. 

Hay algunas formas diferentes de usar el simulador. Una forma es generar algunos trabajos aleatorios y ver si puedes descubrir cómo se comportarán dado el planificador MLFQ. Por ejemplo, si deseas crear una carga de trabajo de tres trabajos generados aleatoriamente, escribe:

```
  python mlfq.py -j 3
```

Esto genera una carga de trabajo aleatoria de tres trabajos (como se especifica), en el número predeterminado de colas con una serie de configuraciones predeterminadas. Si vuelve a ejecutar con el indicador de resolución en (-c) obtendrás un resultado diferente.

```
  python mlfq.py -j 3 -c 
```

La traza muestra exactamente, en una escala de tiempo de milisegundos por milisegundo, lo que el planificador decidió hacer. En este ejemplo, se comienza ejecutando el Trabajo 0 durante 7 ms hasta que el Trabajo 0 emite una E/S; esto es completamente predecible, ya que la frecuencia de E/S del trabajo 0 se establece en 7 ms, lo que significa que cada 7 ms que se ejecuta, emitirá una E/S y esperará a que se complete antes de continuar. En ese punto, el planificador cambia al Trabajo 1, que solo se ejecuta 2 ms antes de emitir una E/S.

El planificador imprime la traza de ejecución completa de esta manera, y finalmente también calcula la respuesta, el TAT para cada trabajo
así como un promedio.

También puedes controlar otros aspectos de la simulación. Por ejemplo, puede especificar cuántas colas le gustaría tener el sistema (-n) y cuál debería ser la longitud del cuanta para todas esas colas (-q). Si desea aún más control y una longitud de cuantas variadas por cola, puede especificar la longitud del cuanta (intervalo de tiempo) para cada cola con -Q, por ejemplo, `-Q 10,20,30` simula un planificador con tres colas, con la cola de mayor prioridad con un segmento de tiempo de 10 ms, el siguiente segmento de tiempo más alto de 20 ms, y la cola de baja prioridad con un segmento de tiempo de 30 ms.

También puedes controlar por separado cuánto tiempo hay asignado por cola también. Esto se puede configurar para todas las colas con -a, o por cola con -A, por ejemplo, -A 20,40,60 establece la asignación de tiempo por cola en 20ms, 40ms y 60ms, respectivamente.

Si estás generando trabajos aleatoriamente, también puedes controlar cuánto tiempo podrían ejecutarse (-m), o con qué frecuencia generan E/S (-M). Sin embargo, si deseas tener más control sobre las características exactas de los trabajos que se ejecutan en el sistema, puede usar -l que le permite especificar el conjunto exacto de trabajos que deseas simular .

La lista tiene la forma: `x1, y1, z1: ​​x2, y2, z2: ...` donde `x` es el tiempo de inicio del trabajo, `y` es el tiempo de ejecución (es decir, cuánto tiempo de CPU necesita) y `z` la frecuencia de E/S (es decir, después de ejecutar `z` ms, el trabajo emite una E/S; si `z` es `0`, no se emiten E/S).

```
  python mlfq.py --jlist 0,180,0:100,20,0 -q 10
```

Ejecutar el simulador de esta manera crea un MLFQ de tres niveles, con cada nivel con un intervalo de tiempo de 10 ms. Se crean dos trabajos: el trabajo 0 que comienza en el tiempo 0, se ejecuta durante 180 ms en total y nunca emite una E/S, el trabajo 1 comienza a los 100 ms, solo necesita 20 ms de tiempo de CPU para completarse y tampoco emite E/S.

Finalmente, hay tres parámetros más de interés. El indicador -B, si se establece en un valor distinto de cero, aumenta todos los trabajos a la cola de mayor prioridad cada N milisegundos, cuando se invoca como tal:

```
  python mlfq.py -B N
```
El planificador usa esta función para evitar el *starvation*, sin embargo, está desactivado por defecto.

El indicador -S invoca las reglas 4a y 4b dadas en clase, lo que significa que si un trabajo emite una E/S antes de completar su segmento de tiempo, volverá a la misma cola de prioridad cuando reanude la ejecución, con su segmento de tiempo completo intacto. Esto permite el juego del planificador.

Finalmente, puedes cambiar fácilmente la duración de una E/S utilizando el indicador -i. De manera predeterminada en este modelo, cada E/S lleva una cantidad fija de tiempo de 5 milisegundos o lo que sea que establezca con este indicador.

También puede jugar si los trabajos que solo completan una E/S se mueven al principio de la cola en la que están o hacia atrás, con el indicador -I.


### Ejercicios

1. Ejecuta algunos problemas generados aleatoriamente con solo dos trabajos y dos colas. Calcula la traza de  ejecución de MLFQ para cada uno. Limita la duración de cada trabajo y desactiva las E/S.

1. ¿Cómo ejecutaría el planificador para reproducir cada uno de los ejemplos de la diapositivas?

1. ¿Cómo configurarías los parámetros del planificador para que se comporten como un planificador round-robin?

1. Crea una carga de trabajo con dos trabajos y con  parámetros del planificador para que un trabajo aproveche las Reglas 4a y 4b más antiguas (activadas con el indicador -S) para jugar el planificador y obtener el 99% de la CPU en un intervalo de tiempo particular.

1. Dado un sistema con una longitud de cuanra de 10 ms en su cola más alta, ¿con qué frecuencia tendría que aumentar los trabajos al nivel de prioridad más alto (con el indicador -B) para garantizar que una sola ejecución larga (y potencialmente con starvation) ) trabajo obtiene al menos el 5% de la CPU?

1. Una pregunta que surge en la planificación es qué al final de una cola para agregar un trabajo que acaba de terminar la E/S; el indicador -I cambia este comportamiento para este simulador de planificacion. Juega con algunas cargas de trabajo y vea si puede ver el efecto de este flag.


## Cuota proporcional y lotería

El programa, loteria.py, permite ver cómo funciona un planificador de lotería. Como siempre, hay dos pasos para ejecutar el programa. Primero, se ejecuta sin el indicador -c: esto  muestra qué problema resolver sin revelar las respuestas.

```
   python loteria.py -j 2 -s 0
```

Cuando ejecutas el simulador de esta manera, primero se asignan algunos trabajos aleatorios (aquí de longitudes 8 y 4), cada uno con un cierto número de tickets (aquí 75 y 25, respectivamente). El simulador también te brinda una lista de números aleatorios, que necesitará para determinar qué hará el planificador de lotería. Los números aleatorios se eligen entre 0 y un número grande; por lo tanto, tendrás que usar el operador de módulo para calcular el ganador de la lotería (es decir, el ganador debe igualar este módulo de número aleatorio con el número total de tickets en el sistema).

Ejecutar con -c muestra exactamente lo que se supone que debes calcular:

```
   python loteria.py -j 2 -s 0 -c
```

Como puedes ver en el trace, lo que se supone que debes hacer es usar el número aleatorio para determinar qué ticket es el ganador. Luego, dado el ticket ganador, averiguar qué trabajo debe ejecutarse. Repite esto hasta que todos los trabajos hayan terminado de ejecutarse. Es tan simple como eso: solo estás emulando lo que hace el planificador de lotería, ¡pero a mano!.

Veamos la primera decisión tomada en el ejemplo anterior. En este punto, tenemos dos trabajos (el trabajo 0, que tiene un tiempo de ejecución de 8 y 75 tickets, y el trabajo 1, que tiene un tiempo de ejecución de 4 y 25 tickets). El primer número aleatorio que se nos da es 511275. Como hay 100 tickets en el sistema, 511275% 100 es 75, y por lo tanto 75 es nuestro ticket ganador.

Si el boleto 75 es el ganador, simplemente buscamos en la lista de trabajos hasta que lo encontremos. La primera entrada, para el trabajo 0, tiene 75 boletos (0 a 74), y por lo tanto no gana,  la siguiente entrada es para el trabajo 1, y por lo tanto hemos encontrado nuestro ganador, por lo que ejecutamos el trabajo 1 para la longitud cuanta (1 en este ejemplo). Todo esto se muestra  de la siguiente manera:

```
  Random 511275 -> Winning ticket 75 (of 100) -> Run 1
     Jobs:  (  job:0 timeleft:8 tix:75 ) (* job:1 timeleft:4 tix:25 )
```

Como puedes ver, la primera línea resume lo que sucede, y la segunda simplemente muestra toda la cola de trabajos, con un * que indica qué trabajo se eligió.

El simulador tiene algunas otras opciones, la mayoría de las cuales deberían explicarse por sí mismas. En particular, el indicador -l/- jlist se puede usar para especificar un conjunto exacto de trabajos y sus valores de ticket, en lugar de usar siempre listas de trabajos generadas aleatoriamente.

### Ejercicios

1. Calcula las soluciones para simulaciones con 3 trabajos y semillas aleatorias de 1, 2 y 3.

1. Ahora ejecuta con dos trabajos específicos: cada uno de longitud 10, pero uno (trabajo 0) con solo 1 ticket y el otro (trabajo 1) con 100 (por ejemplo, -l 10: 1,10: 100). ¿Qué sucede cuando el número de boletos está tan desequilibrado? ¿Se ejecutará alguna vez el trabajo 0 antes de que se complete el trabajo 1? ¿Con qué frecuencia? En general, ¿qué hace un desequilibrio de tal ticket al comportamiento de la planificación de lotería?

1. Cuando se ejecuta con dos trabajos de longitud 100 y asignaciones de tickets iguales de 100 (-l 100: 100,100: 100), ¿qué tan equitativo es el planificador? Ejecuta con algunas semillas aleatorias diferentes para determinar la respuesta (probabilística).

1. ¿Cómo cambia su respuesta a la pregunta anterior a medida que aumenta el tamaño cuántico (-q)?

1. ¿Puedes hacer una versión del gráfico que se encuentra en las presentaciones? ¿Qué más valdría la pena explorar? ¿Cómo se vería el gráfico con un planificador stride?.

## Planificación del multiprocesador

El programa multi.py, es un simulador del planificador multi-CPU. Por defecto, hay una o más CPU en el sistema (como se especifica con el indicador -n). Por lo tanto, para ejecutar con 4 CPU tu simulación, escribe:

```
  python mlfq.py -n 4
```

Cada CPU tiene una memoria caché, que puede contener datos importantes de uno o más procesos en ejecución. El tamaño de cada caché de la CPU se establece mediante el indicador -M. Por lo tanto, para hacer que cada caché tenga un tamaño de '100' en tu sistema de 4 CPU, ejecuta:

```
   python multi.py -n 4 -M 100
```

Para ejecutar una simulación, se necesita algunos trabajos para programar. Hay dos maneras de hacer esto. El primero es dejar que el sistema construye algunos trabajos con características aleatorias (este es el valor predeterminado, es decir, si no especifica nada, obtiene esto). También hay algunos controles para controlar la naturaleza de los trabajos generados aleatoriamente. Lo segundo es especificar una lista de trabajos para que el sistema los programe con precisión; Esto también se describe con más detalle.

Cada trabajo tiene dos características. El primero es su "tiempo de ejecución" (cuántas unidades de tiempo se ejecutará). El segundo es su "tamaño de conjunto de trabajo" (cuánto espacio de caché se necesita para ejecutarse eficientemente). Si estás generando trabajos al azar, puede controlar el rango de estos valores mediante el uso de -R (indicador de tiempo de ejecución máximo) y -W (indicador de tamaño máximo de conjunto de trabajo). El generador aleatorio generará valores que no son más grandes que esos.

Si estás especificando trabajos a mano, establezca cada uno de estos explícitamente, utilizando el indicador -L. Por ejemplo, si desea ejecutar dos trabajos, cada uno con un tiempo de ejecución de 100, pero con diferentes tamaños de conjuntos de trabajo de 50 y 150, respectivamente, puedes ejecutar:

```
  python multi.py -n 4 -M 100 -L 1:100:50,2:100:150
```

Ten en cuenta que se asignó a cada trabajo un nombre, '1' para el primer trabajo y '2' para el segundo. Cuando los trabajos se generan automáticamente, los nombres se asignan automáticamente (solo con números).

La eficacia con la que se ejecuta un trabajo en una CPU en particular depende de si la memoria caché de esa CPU contiene actualmente el conjunto de trabajo del trabajo dado. Si no lo hace, el trabajo se ejecuta lentamente, lo que significa que solo se resta 1 tick de su tiempo de ejecución del tiempo restante por cada tick del reloj. Este es el modo en el que el caché está 'inactivo' para ese trabajo (es decir, todavía no contiene el conjunto de trabajo). Sin embargo, si el trabajo se ejecutó anteriormente en la CPU durante "tiempo suficiente", la memoria caché de la CPU ahora está "activa" y el trabajo se ejecutará más rápidamente,  dependiendo del valor del flag -r, que es la 'tasa de calentamiento (warmup)'. Aquí, es algo así como 2x por defecto, pero puede cambiarlo según sea necesario.

El flag -w, establece el "tiempo de calentamiento". Por defecto, es algo así como 10 unidades de tiempo. Por lo tanto, si un trabajo se ejecuta durante 10 unidades de tiempo, la memoria caché en esa CPU se calienta y luego el trabajo comienza a ejecutarse más rápido. Todo esto, por supuesto, es una aproximación de cómo funciona un sistema real.

La primera política (predeterminada) es simple: una cola de planificación centralizada, con una asignación de trabajos RR  para CPU inactivas. El segundo es un enfoque de cola de planificación por CPU (activado con -p), en el que los trabajos se asignan a una de las N colas de planificación (una por CPU). En este enfoque, una CPU inactiva (en ocasiones) se asoma a la cola de otra CPU y roba un trabajo para mejorar el equilibrio de carga. La frecuencia con la que se hace esto se establece mediante un intervalo de 'vistazo (peek)' (establecido por el indicador -P).

### Ejercicios

1. Para comenzar, aprendamos cómo usar el simulador para estudiar cómo construir un planificador multiprocesador efectivo. La primera simulación ejecutará solo un trabajo, que tiene un tiempo de ejecución de 30 y un tamaño de conjunto de trabajo de 200. Ejecuta este trabajo (llamado trabajo 'a' aquí) en una CPU simulada de la siguiente manera: `python multi.py -n 1 -L a: 30: 200`. ¿Cuánto tiempo llevará completar? Activa el indicador -c para ver una respuesta final y el indicador -t para ver un seguimiento del trabajo y cómo está planificado.

1. Ahora aumente el tamaño de la memoria caché para que el conjunto de trabajo del trabajo (tamaño = 200) se ajuste a la memoria caché (que, de forma predeterminada, es  de tamaño = 100); por ejemplo, ejecuta `python multi.py -n 1 -L a: 30: 200 -M 300`. ¿Puedes predecir qué tan rápido se ejecutará el trabajo una vez que encaje en la memoria caché? 

1. Ejecuta la misma simulación anterior, pero esta vez con el tiempo restante de rastreo habilitado (-T). Este indicador muestra tanto el trabajo que se planificó en una CPU en cada paso de tiempo, así como la cantidad de tiempo de ejecución que le queda al trabajo después de que se haya ejecutado cada tick. ¿Qué notas acerca de cómo disminuye esa segunda columna?.

1. Para mostrar el estado de cada caché de CPU para cada trabajo, utiliza el indicador -C. Para cada trabajo, cada caché mostrará un espacio en blanco (si el caché está frío para ese trabajo) o una 'w' (si el caché está caliente para ese trabajo). ¿En qué punto el caché se calienta para el trabajo "a" en este ejemplo? ¿Qué sucede cuando cambia el parámetro de tiempo de calentamiento (-w) a valores más bajos o más altos que los predeterminados?.

1.  Sean los siguientes tres trabajos en un sistema de dos CPU (es decir, escribe `python multi.py -n 2 -L a: 100: 100, b: 100: 50, c: 100: 50`) ¿Puedes predecir cuánto tiempo tomará  un planificador centralizado round-robin?. Usa -c para  corroborar los resultados y luego analiza  los detalles con -t para ver  paso a paso y luego -C para ver si los cachés se calentaron efectivamente para estos trabajos. ¿Que notaste?.


## Nota del autor del solucionario
El solucionario de este laboratorio no es oficial y está incompleto.