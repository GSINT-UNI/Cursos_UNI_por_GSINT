# Notas del laboratorio 2 CC-571

En estas notas, veremos los siguientes temas:

* Espacio de direcciones
* API de memoria
* Traducción de direcciones
* Segmentación

## Espacio de direcciones

En esta parte de laboratorio, aprenderemos algunas herramientas útiles para examinar el uso de la memoria virtual en sistemas basados ​​en Linux.

### Ejercicios

1. La primera herramienta de Linux que debe consultar es la herramienta `free`. Escribe `man free` y lee toda la página del manual.

1. Ahora, ejecuta `free`, quizás usando algunos de los argumentos que podrían ser útiles (por ejemplo, -m, para mostrar el total de memoria en megabytes). ¿Cuánta memoria hay en tu sistema? ¿Cuánto es `free`? ¿Estos números coinciden con tu intuición?

1. Crea un pequeño programa que usa una cierta cantidad de memoria, llamada `memoria-user.c`. Este programa debería tomar un argumento de línea de comandos: la cantidad de megabytes de memoria que usará. Cuando se ejecuta, debe asignar un array y transmitir constantemente a través del array, tocando cada entrada. El programa debe hacer esto indefinidamente o, tal vez, durante un cierto período de tiempo también especificado en la línea de comando.

1. Probemos una herramienta más, conocida como `pmap`. Dedica algo de tiempo y lea la página del manual de `pmap` en detalle.

1. Para usar `pmap`, debe conocer la ID del proceso que le interesa. Por lo tanto, primero ejecute `ps auxw` para ver una lista de todos los procesos, luego, elija uno interesante, como un navegador. También puede usar tu programa anterior en este caso (de hecho, incluso puede hacer que ese programa llame a `getpid()` e imprima su PID para su conveniencia).

1. Ahora ejecuta `pmap` en algunos de estos procesos, utilizando varios indicadores (como -X) para revelar muchos detalles sobre el proceso. ¿Que ves? ¿Cuántas entidades diferentes forman un espacio de direcciones moderno, en oposición a nuestra simple concepción de `code/stack/heap?.

1. Finalmente, ejecutemos `pmap` en tu programa `memoria-user`, con diferentes cantidades de memoria usada. que ves aquí? ¿La salida de `pmap` coincide con sus expectativas?.

## API de memoria

En esta parte del laboratorio, se familiarizará con la asignación de memoria. Primero, escribireos algunos programas con errores . Luego, se utilizara algunas herramientas para ayudarlo a encontrar los errores que insertó. Entonces, te darás cuenta de lo increíbles que son estas herramientas y las usarás en el futuro como `gdb` y `valgrind`.

### Ejercicios

1.  Escribe un programa simple llamado `null.c` que crea un puntero a un entero, lo establezca en NULL y luego intente desreferenciarlo. Compila esto en un ejecutable llamado `null`. ¿Qué sucede cuando ejecutas este programa?

1. A continuación, compila este programa con la información del símbolo incluida (con el indicador -g). Al hacerlo, vamos a poner más información en el ejecutable, lo que permite al depurador acceder a información más útil sobre nombres de variables y similares. Ejecuta el programa debajo del depurador escribiendo `gdb null` y luego, una vez que gdb se esté ejecutando, escriba `run`. ¿Qué te muestra gdb?

1. Finalmente, usa la herramienta valgrind en este programa. Utilizaremos la herramienta `memcheck` que es parte de valgrind para analizar lo que sucede. Ejecuta esto escribiendo lo siguiente: `valgrind --leak-check = yes null`. ¿Qué sucede cuando ejecutas esto? ¿Puedes interpretar el resultado de la herramienta?.

1. Escribe un programa que asigne memoria usando `malloc()` pero se te olvida de liberarlo antes de salir. ¿Qué sucede cuando se ejecuta este programa? ¿Puedes usar gdb para encontrar algún problema? ¿Qué tal te va con valgrind  (nuevamente con  `--leak-check = yes`)?.

1. Escribe un programa que cree un array de enteros llamados `data` de tamaño 100 usando `malloc`; luego, configura `data[100]` a cero. ¿Qué sucede cuando ejecutas este programa? ¿Qué sucede cuando ejecuta este programa usando valgrind? ¿Es correcto el programa?.

1. Crea un programa que asigne un array de enteros (como arriba), los libera y luego intente imprimir el valor de uno de los elementos del array. ¿Se ejecuta el programa? ¿Qué sucede cuando usas valgrind?.

1. Ahora pase un  puntero en el medio del array que asignó anteriormente. ¿Qué ocurre? ¿Necesitas otras herramientas para encontrar este tipo de problema?.

## Traducción de direcciones

El programa reasignacion.py te permite ver cómo se realizan las traducciones de direcciones en un sistema con registros de base y límites. Como antes, hay dos pasos para ejecutar el programa para probar su comprensión de la base y los límites. Primero, ejecutar sin el indicador -c para generar un conjunto de traducciones y ver si puede realizar correctamente las traducciones de direcciones tu mismo. Luego, cuando hayas terminado, utilices  el indicador -c para verificar tus respuestas.

En este laboratorio, asumiremos un espacio de direcciones ligeramente diferente, con heap y stack en los extremos opuestos del espacio. Más bien, supondremos que el espacio de direcciones tiene una sección de código, luego un stack de tamaño fijo (pequeño) y un heap que crece hacia abajo después, con un aspecto similar al que se ve en la figura. En esta configuración, solo hay una dirección de crecimiento, hacia las regiones más altas del espacio de direcciones.


```sh
  -------------- 0KB
  |    Code    |
  -------------- 2KB
  |   Stack    |
  -------------- 4KB
  |    Heap    |
  |     |      |
  |     v      |
  -------------- 7KB
  |   (free)   |
  |     ...    |
```
En la figura, el registro de límites se establecería en 7~ KB, ya que eso representa el final del espacio de direcciones. Las referencias a cualquier dirección dentro de los límites se considerarán legales; las referencias por encima de este valor están fuera de los límites y, por lo tanto, el hardware generaría una excepción.

Para ejecutar con los indicadores predeterminados, debes escribir reasignacion.py en la línea de comando.

```
  python reasignacion.py
```

Para cada dirección virtual, escribe la dirección física a la que se traduce o escribe que es una dirección fuera de los límites (una violación de la segmentación). Para este problema, debes asumir un espacio de dirección virtual simple de un tamaño determinado.

Como puedes ver, la tarea simplemente genera direcciones virtuales aleatorias. Para cada uno, debe determinar si está dentro de los límites y, de ser así, determinar a qué dirección física se traduce. Ejecutar  -c nos da los resultados de estas traducciones, es decir, si son válidas o no, y si son válidas, las direcciones físicas resultantes. Por conveniencia, todos los números se dan en hexadecimal y decimal.

```
  python reasignacion.py -c
```
Con una dirección base de 12418 (decimal), la dirección 430 está dentro de los límites (es decir, es menor que el registro límite de 472) y, por lo tanto, se traduce en 430 agregados a 12418 o 12848. Algunas de las direcciones que se muestran arriba están fuera de los límites (523, 802), ya que exceden los límites.

Hay algunos indicadores que se puede usar para controlar lo que está sucediendo mejor. En particular, puede controlar el tamaño del espacio de direcciones virtuales (-a), el tamaño de la memoria física (-p), el número de direcciones virtuales para generar (-n) y los valores de los registros de base y límites para este proceso (-b y -l, respectivamente).

### Ejercicios

1. Ejecuta con las semillas 1, 2 y 3, y calcula si cada dirección virtual generada por el proceso está dentro o fuera de los límites. Si está dentro de los límites, calcula la traducción.

1. Ejecuta con estos indicadores: -s 0 -n 10. ¿A qué valor ha establecido -l (el registro de límites) para garantizar que todas las direcciones virtuales generadas estén dentro de los límites?

1. Ejecuta con estos indicadores: -s 1 -n 10 -l 100. ¿Cuál es el valor máximo en el que se puede establecer el registro base, de modo que el espacio de direcciones todavía se ajuste a la memoria física en su totalidad?

1. Ejecuta algunos de los mismos problemas anteriores, pero con espacios de direcciones más grandes (-a) y memorias físicas (-p).

5. ¿Qué fracción de las direcciones virtuales generadas aleatoriamente son válidas, en función del valor del registro de límites? Realiza un gráfico con diferentes semillas aleatorias, con valores límite que van desde 0 hasta el tamaño máximo del espacio de direcciones.



## Segmentación

El programa segmentacion.py, permite ver cómo se realizan las traducciones de direcciones en un sistema con segmentación. La segmentación que usa este sistema es bastante simple: un espacio de direcciones tiene solo dos segmentos; Además, el bit superior de la dirección virtual generada por el proceso determina en qué segmento se encuentra la dirección: 0 para el segmento 0 (donde, por ejemplo, residirían el código y el heap) y 1 para el segmento 1 (donde vive el stack). El segmento 0 crece en una dirección positiva (hacia direcciones más altas), mientras que el segmento 1 crece en la dirección negativa.

Visualmente, el espacio de direcciones se ve así:

```
 --------------- virtual address 0
 |    seg0     |
 |             |
 |             |
 |-------------|
 |             |
 |             |
 |             |
 |             |
 |(unallocated)|
 |             |
 |             |
 |             |
 |-------------|
 |             |
 |    seg1     |
 |-------------| virtual address max (size of address space)
```

Con la segmentación, hay un par base/límite de registros por segmento. Por lo tanto, en este problema, hay dos pares de base/límite. La base del segmento 0 indica qué dirección física se ha colocado en la parte superior del segmento 0 en la memoria física y el límite indica qué tan grande es el segmento. La base del segmento -1 indica dónde se ha colocado la parte inferior del segmento 1 en la memoria física y el límite correspondiente también nos dice qué tan grande es este segmento (o qué tan lejos crece en la dirección negativa).

Como antes, hay dos pasos para ejecutar el programa para probar su comprensión de la segmentación. Primero, ejecuta sin el indicador "-c" para generar un conjunto de traducciones y ver si puede realizar correctamente las traducciones de la dirección tu mismo. Luego, cuando hayas terminado, ejecuta con el indicador "-c" para verificar sus respuestas.

Por ejemplo, para ejecutar con los indicadores predeterminados, escribe:

```
  python segmentacion.py 
```

Luego, después de haber calculado las traducciones en el trace de la dirección virtual, ejecuta el programa nuevamente con el indicador "-c". Verá lo siguiente (sin incluir la información redundante):

```
    Virtual Address Trace
    VA  0: 0x0000020b (decimal:  523) --> SEGMENTATION VIOLATION (SEG1)
    VA  1: 0x0000019e (decimal:  414) --> VALID in SEG0: 0x00001c88 (decimal: 7304)
    VA  2: 0x00000322 (decimal:  802) --> VALID in SEG1: 0x00001176 (decimal: 4470)
    VA  3: 0x00000136 (decimal:  310) --> VALID in SEG0: 0x00001c20 (decimal: 7200)
    VA  4: 0x000001e8 (decimal:  488) --> SEGMENTATION VIOLATION (SEG0)
```

Como puedes ver, con -c, el programa traduce las direcciones y, por lo tanto, puedes verificar si comprendes cómo un sistema que usa la segmentación traduce las direcciones.

Por supuesto, hay algunos parámetros que puedes usar para darte problemas diferentes. Un parámetro particularmente importante es el parámetro -s o -seed, que te permite generar diferentes problemas al pasar una semilla aleatoria diferente. Por supuesto, debes asegurarte de usar la misma semilla aleatoria cuando genere un problema y luego lo resuelva.

También hay algunos parámetros que puede usar para jugar con espacios de direcciones de diferentes tamaños y memorias físicas. Por ejemplo, para experimentar con la segmentación en un sistema pequeño, puedes escribir:

```
  python segmentacion.py -s 100 -a 16 -p 64
```


y lo que le dice al  programa es que genere direcciones virtuales para un espacio de direcciones de 16 bytes ubicado en algún lugar de una memoria física de 64 bytes. Como puedes ver, las direcciones virtuales resultantes son pequeñas (12, 8, 1, 7 y 0). Como también puedes ver, el programa selecciona un pequeño registro base y valores límite, según corresponda. Ejecuta con -c para ver las respuestas.

Este ejemplo también debería mostrar exactamente lo que significa cada par de bases. Por ejemplo, la base del segmento 0 se establece en una dirección física de 49 (decimal) y tiene un tamaño de 4 bytes. Por lo tanto, las direcciones virtuales 0, 1, 2 y 3 están en el segmento 0 y son válidas, y se asignan a las direcciones físicas 49, 50, 51 y 52, respectivamente.

Un poco más complicado es el segmento 1 de crecimiento en dirección negativa. En el ejemplo anterior, el registro base del segmento 1 se establece en la dirección física 32, con un tamaño de 5 bytes. Eso significa que los últimos cinco bytes del espacio de direcciones virtuales, en este caso 11, 12, 13, 14 y 15, son direcciones virtuales válidas, y que se asignan a las direcciones físicas 27, 28, 29, 30 y 31, respectivamente.


Ten en cuenta que puedes especificar valores más grandes agregando una "k", "m" o incluso "g" en los valores que pasa con los indicadores -a o -p, como en "kilobytes", "megabytes" y "gigabytes ". Por lo tanto, si deseaa hacer algunas traducciones con un espacio de direcciones de 1 MB establecido en una memoria física de 32 MB, puede escribir:

```
  python segmentacion.py -a 1m -p 32m
```

Si deseaa ser aún más específico, puede establecer el registro base y limitar los valores de registro tu mismo, con los registros --b0, --l0, --b1 y --l1. 


### Ejercicios

1. Usemos un pequeño espacio de direcciones para traducir algunas direcciones. Aquí hay un conjunto simple de parámetros con algunas semillas aleatorias diferentes; puedes traducir las direcciones?

```
  segmentacion.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
  segmentacion.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
  segmentacion.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2

```
1. Ahora, veamos si entendemos este pequeño espacio de direcciones que hemos construido (usando los parámetros de la pregunta anterior). ¿Cuál es la dirección virtual legal más alta en el segmento 0? ¿Qué pasa con la dirección virtual legal más baja en el segmento 1? ¿Cuáles son las direcciones ilegales más bajas y más altas en todo este espacio de direcciones? Finalmente, ¿cómo ejecutarías segmentacion.py con el indicador -A para probar si tienes razón?

1. Digamos que tenemos un pequeño espacio de direcciones de 16 bytes en una memoria física de 128 bytes. ¿Qué base y límites establecería para que el simulador genere los siguientes resultados de traducción para la secuencia de direcciones especificada: valid, violation,..., violation, valid, valid?.  Asume los siguientes parámetros:

```
  segmentacion.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 ? --l0 ? --b1 ? --l1 ?
```




## Nota del autor del solucionario
Los programas escritos `memory-user.c` y `null.c` no pertenecen a la solución oficial.