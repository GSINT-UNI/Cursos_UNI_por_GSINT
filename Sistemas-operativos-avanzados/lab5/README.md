# Notas del laboratorio 5 CC-571

En estas notas, veremos los siguientes temas:

* Mecanismos de memoria
* Políticas de reemplazo de página

### Mecanismo de memoria

En esta parte de laboratorio, se investigará el rendimiento del intercambio con un programa  que se encuentra en *mem.c*. El programa simplemente asigna un array de enteros de cierto tamaño, y luego procede a recorrerlo (repetidamente), incrementando cada valor en el array.

Escribe *make* para compilarlo (y mira el simple archivo Makefile para obtener detalles sobre cómo funciona la compilación).

Luego, escribe ./mem seguido de un número para ejecutarlo. El número es el tamaño (en MB) del array. Por lo tanto, para ejecutar con un array pequeño (tamaño 1 MB) se hace:

```shell
./mem 1
```

y para ejecutar con un array más grande (tamaño 1 GB):

```shell
./mem 1024
```

El programa imprime el tiempo que lleva pasar por cada ciclo, así como el ancho de banda (en MB/s). El ancho de banda es particularmente interesante de conocer, ya que le da una idea de qué tan rápido el sistema que está utilizando puede moverse a través de los datos. En sistemas modernos, esto es probable que esté en el rango de GB/s.

Así es como se ve la salida para una ejecución típica:

```shell
./mem 1000
```

El programa primero te dice cuánta memoria asignó (en bytes, MB y en la cantidad de enteros), y luego comienza a recorrer el array. 

El programa continúa haciendo lo mismo una y otra vez, para los bucles 1, 2, etc.

Importante: para detener el programa, debes matarlo. Esta tarea se realiza en Linux (y en todos los sistemas basados en Unix) escribiendo control-C (^ C).

Ten en cuenta que cuando el programa se ejecuta con arrays de tamaño pequeños, no se imprimirán los números de rendimiento de cada bucle. Por ejemplo:

```shell
./mem 1
```

En este caso, el programa solo imprime una muestra de las salidas.

El código en sí es simple de entender. La primera parte importante es una asignación de memoria:

```c++
int *x = malloc(size_in_bytes);
```

Entonces, comienza el bucle principal:

```c#
while (1) {
	x[i++] += 1;
```

El resto es solo tiempo e impresión de información. 

Gran parte de la tarea gira en torno al uso de la herramienta *vmstat* para monitorear lo que sucede con el sistema. Lee la página de manual de *vmstat* (escriba *man vmstat*) para obtener detalles sobre cómo funciona y qué significa cada columna de salida.

### Ejercicios

1. Primero, abre dos conexiones de terminal separadas de la misma máquina, de modo que puedas ejecutar fácilmente algo en una ventana y en la otra ventana. Ahora, en una ventana, ejecuta *vmstat 1*, que muestra estadísticas sobre el uso de la máquina cada segundo.  Deja esta ventana ejecutando *vmstat* para el resto de los ejercicios.

   Ahora, ejecutaremos el programa mem.c pero con muy poco uso de memoria. Esto se puede lograr escribiendo ./mem 1 (que usa solo 1 MB de memoria). ¿Cómo cambian las estadísticas de uso de la CPU cuando se ejecuta *mem*? ¿Los números en la columna *user time* tienen sentido? ¿Cómo cambia esto cuando se ejecuta más de una instancia de *mem* a la vez?

2. Ahora comencemos a ver algunas de las estadísticas de memoria mientras ejecuta *mem*. Nos centraremos en dos columnas: *swpd* (la cantidad de memoria virtual utilizada) y *free* (la cantidad de memoria inactiva). Ejecuta ./mem 1024 (que asigna 1024 MB) y observa cómo cambian estos valores. Luego elimina el programa en ejecución (escribiendo control-c) y observa nuevamente cómo cambian los valores. ¿Qué notas sobre los valores? En particular, ¿cómo cambia la columna *free* cuando sale del programa? ¿La cantidad de memoria libre aumenta en la cantidad esperada cuando *mem* sale?.

3. A continuación, veremos las columnas *swap* (*si* y *so*), que indican cuánto intercambio se está llevando a cabo desde y hacia el disco. Por supuesto, para activarlos, deberás ejecutar *mem* con grandes cantidades de memoria. Primero, examina cuánta memoria libre hay en tu sistema Linux (por ejemplo, escribiendo *cat/proc/meminfo* . Escribe *man proc* para obtener detalles sobre el sistema de archivos /proc y los tipos de información que puedes encontrar allí). Una de las primeras entradas en */proc/meminfo* es la cantidad total de memoria en tu sistema. Supongamos, algo así como 8 GB de memoria; si es así, comienza ejecutando *mem 4000* (aproximadamente 4 GB) y observando las columnas de intercambio de entrada/salida. ¿Alguna vez dan valores distintos de cero? Luego, intenta con 5000, 6000, etc. ¿Qué sucede con estos valores cuando el programa ingresa al segundo ciclo (y más allá), en comparación con el primer ciclo? ¿Cuántos datos (total) se intercambian dentro y fuera durante el segundo, tercer y posteriores bucles? (¿tienen sentido los números?).

4. Realiza los mismos experimentos que antes, pero ahora mira las otras estadísticas (como la utilización de la CPU y las estadísticas de bloqueo de E/S). ¿Cómo cambian cuando se está ejecutando *mem*?.

5. Ahora examinemos el rendimiento. Elige una entrada para *mem* que se ajuste cómodamente a la memoria (digamos 4000 si la cantidad de memoria en el sistema es de 8 GB). ¿Cuánto dura el bucle 0 (y los bucles posteriores 1, 2, etc.)? Ahora elige un tamaño cómodamente más allá del tamaño de la memoria (digamos 12000 nuevamente suponiendo 8 GB de memoria). ¿Cuánto tardan los bucles aquí? ¿Cómo se comparan los números de ancho de banda? ¿Qué tan diferente es el rendimiento cuando se intercambia constantemente versus ajustar todo en la memoria?. Realiza un gráfico, con el tamaño de la memoria utilizada por *mem* en el eje x y el ancho de banda de acceso a dicha memoria en el eje y? Finalmente, ¿cómo se compara el rendimiento del primer bucle con el de los bucles posteriores, tanto para el caso en que todo cabe en la memoria como en el que no?.

### Políticas de reemplazo de página

En esta parte del laboratorio se utiliza un simulador, paging-politicas.py,  que permite jugar con diferentes políticas de reemplazo de página. Por ejemplo, examinemos cómo funciona LRU con una serie de referencias de página con un caché de tamaño 3:

```python
 python paging-politicas.py --addresses=0,1,2,0,1,3,0,3,1,2,1  --policy=LRU --cachesize=3 -c
```

Y lo que deberías ver es algo así:

```python
Argument addresses 0,1,2,0,1,3,0,3,1,2,1
Argument addressfile 
Argument numaddrs 10
Argument policy LRU
Argument clockbits 2
Argument cachesize 3
Argument maxpage 10
Argument seed 0
Argument notrace False

Resolviendo...

Acceso: 0  MISS LRU ->          [0] <- MRU Reemplazado:- [Hits:0 Misses:1]
Acceso: 1  MISS LRU ->       [0, 1] <- MRU Reemplazado:- [Hits:0 Misses:2]
Acceso: 2  MISS LRU ->    [0, 1, 2] <- MRU Reemplazado:- [Hits:0 Misses:3]
Acceso: 0  HIT  LRU ->    [1, 2, 0] <- MRU Reemplazado:- [Hits:1 Misses:3]
Acceso: 1  HIT  LRU ->    [2, 0, 1] <- MRU Reemplazado:- [Hits:2 Misses:3]
Acceso: 3  MISS LRU ->    [0, 1, 3] <- MRU Reemplazado:2 [Hits:2 Misses:4]
Acceso: 0  HIT  LRU ->    [1, 3, 0] <- MRU Reemplazado:- [Hits:3 Misses:4]
Acceso: 3  HIT  LRU ->    [1, 0, 3] <- MRU Reemplazado:- [Hits:4 Misses:4]
Acceso: 1  HIT  LRU ->    [0, 3, 1] <- MRU Reemplazado:- [Hits:5 Misses:4]
Acceso: 2  MISS LRU ->    [3, 1, 2] <- MRU Reemplazado:0 [Hits:5 Misses:5]
Acceso: 1  HIT  LRU ->    [3, 2, 1] <- MRU Reemplazado:- [Hits:6 Misses:5]

Estadisticas hits 6 misses 5  tasa_hit 54.55
```

El conjunto completo de posibles argumentos para las política de paginación se enumeran en la página siguiente e incluye una serie de opciones para variar la política:

```shell
python paging-politicas.py --help
```

Como de costumbre, "-c" se usa para resolver un problema en particular, mientras que sin él, los accesos solo se enumeran (y el programa no le dice si un acceso en particular es un acierto o no).

Para generar un problema aleatorio, en lugar de usar  -a / - address para pasar algunas referencias de página, puede pasar  -n/- numaddrs  como el número de direcciones que el programa debe generar aleatoriamente, con   -s/- seed se utiliza para especificar una semilla aleatoria diferente. Por ejemplo:

```shell
python paging-politicas.py -s 10 -n 3
```

Lo que resulta en:

```shell
Asumiendo una politica de reemplazo de FIFO, y un cache de 3 paginas,
averigua si cada una de las referencias de páginas es un acierto o falla
en el cache de la pagina.

Acceso: 5  Acierto/Fallo? Estado de memoria?
Acceso: 4  Acierto/Fallo? Estado de memoria?
Acceso: 5  Acierto/Fallo? Estado de memoria?

```

Como puedes ver, en este ejemplo, especificamos  -n 3, lo que significa que el programa debe generar 3 referencias de página aleatorias, lo que hace: 5, 4 y 5. La semilla aleatoria también se especifica (10), que es lo que nos da esos números particulares. Después de resolver esto, se puede hacer  que el programa resuelva el problema  pasando los mismos argumentos pero con  -c :

```python
python paging-politicas.py -s 10 -n 3 -c
```

 Lo que resulta en:

```shell
Resolviendo...

Acceso: 5  MISS FirstIn ->          [5] <- Lastin  Reemplazado:- [Hits:0 Misses:1]
Acceso: 4  MISS FirstIn ->       [5, 4] <- Lastin  Reemplazado:- [Hits:0 Misses:2]
Acceso: 5  HIT  FirstIn ->       [5, 4] <- Lastin  Reemplazado:- [Hits:1 Misses:2]
```

La política predeterminada es FIFO, aunque hay otras disponibles, incluidas LRU, MRU, OPT (la política de reemplazo óptima, que mira hacia el futuro para ver qué es lo mejor para reemplazar), UNOPT (que es el reemplazo pesimista), RAND (que hace reemplazo aleatorio) y CLOCK (que hace el algoritmo del reloj). El algoritmo CLOCK también toma otro argumento (-b), que indica cuántos bits se deben mantener por página,  cuantos más bits de reloj haya, mejor será el algoritmo para determinar qué páginas mantener en la memoria.

Otras opciones incluyen: -C / - cachesize que cambia el tamaño del caché de la página, -m / - maxpage, que es el número de página más grande que se utilizará si el simulador está generando referencias  y -f / - addressfile, que le permite especificar un archivo con direcciones en ellos, en caso de que desee obtener trazas de una aplicación real o para utilizar una traza larga como entrada.

### Ejercicios

1. ¿Por qué son interesantes estos dos ejemplos?. Explica tu respuesta.

   ```python
   python paging-politicas.py -C 3 -a 1,2,3,4,1,2,5,1,2,3,4,5
   python paging-politicas.py -C 4 -a 1,2,3,4,1,2,5,1,2,3,4,5
   ```

2. Genera direcciones aleatorias con los siguientes argumentos: -s 0 -n 10, -s 1 -n 10 y -s 2 -n 10. Cambia la política de FIFO, a LRU, a OPT. Calcula si cada acceso en dichos  rastreos de direcciones son aciertos o errores.

3. Para un caché de tamaño 5, genera secuencias de referencia de direcciones en el peor de los casos para cada una de las siguientes políticas: FIFO, LRU y MRU (las secuencias de referencia en el peor de los casos causan la mayor cantidad de errores posibles. Para las secuencias de referencia en el peor de los casos,  ¿qué tamaño de caché se necesita para mejorar drásticamente el rendimiento y acercarse a OPT?.

4. Genera una traza aleatoria (use python o perl). ¿Cómo esperaría que las diferentes políticas se desempeñen en tal rastreo?

5. Ahora genera un rastreo con alguna localidad. ¿Cómo puedes generar tal rastreo? ¿Cómo funciona LRU en él? ¿Cuánto mejor que RAND es LRU? ¿Cómo funciona CLOCK? ¿Qué tal CLOCK con diferentes números de bits de reloj?.















