# Notas del laboratorio 4 CC-571

En estas notas, veremos los siguientes temas:

* Administración de espacio libre
* Introducción a la paginación
* TLB
* Tablas pequeñas

### Administración de espacio libre

Este programa, `malloc.py`, permite ver cómo funciona un simple asignador de memoria. 

El programa genera algunas asignaciones aleatorias y free  y permite descubrir cómo sería la lista libre, así como el éxito o el fracaso de cada operación.

```python
python malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c
```

Del resultado se puede ver, que la primera operación de asignación devuelve la siguiente información:

```python
ptr[0] = Alloc(3) devuelto 1004 (busqueda 1 elementos)
Lista libre [ Tam 1 ]: [ addr:1008 sz:92 ]
```

Debido a que el estado inicial de la lista free es solo un elemento grande, es fácil adivinar que la solicitud `Alloc (3)` tendrá éxito. Además, solo devolverá el primer fragmento de memoria y convertirá el resto en una lista free. El puntero devuelto estará más allá del encabezado (dirección: 1004), y el espacio asignado se redondea a 4 bytes, dejando la lista libre con 92 bytes a partir de 1008.

La siguiente operación es Free, de `ptr [0]`, el cual es lo que almacena los resultados de la solicitud de asignación anterior. Como puedes esperar, esta versión  tendrá éxito (por lo tanto, devolverá 0 ), y la lista free ahora parece un poco más complicada:

```python
Free(ptr[0])
devuelto 0
Lista libre [ Tam 2 ]: [ addr:1000 sz:8 ][ addr:1008 sz:92 ]
```

De hecho, debido a que NO usamos coalescing, en la lista libre, ahora tenemos dos elementos en ella, el primero tiene 8 bytes y contiene el espacio que acaba de devolver, y el segundo es el fragmento de 92 bytes.

De hecho, podemos activar coalescing a través del indicador -C:

```pytho
python malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c -C
```

Puede ver que cuando se realizan las operaciones Free , la lista libre realiza calescing como se esperaba: 

Hay otras opciones a explorar:

* `-p BEST o `-p WORST` o `-p FIRST: esta opción permite usar estas tres estrategias diferentes para buscar un fragmento de memoria para usar durante una solicitud de asignación
* ` -l ADDRSORT` o `-l SIZESORT +` o `-l SIZESORT-` o `-l INSERT-FRONT` o  `-l INSERT-BACK`: esta opción  permite mantener la lista libre en un orden particular, por ejemplo, ordenada por la dirección del fragmento libre, tamaño de libre fragmento (ya sea aumentando con un + o disminuyendo con un -), o simplemente devolviendo fragmentos libres de frente (`INSERT-FRONT`) o por atrás (`INSERT-BACK`) de la lista libre.
* `-A list_of_ops`: esta opción permite especificar una serie exacta de solicitudes en lugar de las generadas aleatoriamente. Por ejemplo, si se ejecuta con el indicador  `-A + 10, + 10, + 10, -0, -2`, se asignarán tres fragmentos de 10 bytes (más el encabezado) y luego se liberará el primero ("-0") y luego libera el tercero ("-2"). ¿Cómo será la lista gratuita entonces?.

### Ejercicios

1. Ejecuta  los indicadores `-n 10 -H 0 -p BEST -s 0` para generar algunas asignaciones aleatorias y liberaciones. ¿Puedes predecir qué `alloc ()/ free()` devolverá? ¿Puedes indicar el estado de la lista libre después de cada solicitud? ¿Qué encuentrar sobre la lista free con el tiempo?
2.  ¿En qué se diferencian los resultados cuando se utiliza una política WORST fit para buscar en la lista free  (-p WORST)?, ¿Qué cambia?
3. ¿Qué pasa cuando se usa FIRST fit (`-p FIRST`)? ¿Qué se acelera cuando usas el primer ajuste (firs fit)
4. Para las preguntas anteriores, la forma en que se ordena la lista puede afectar el tiempo que lleva encontrar una ubicación libre para algunas de las políticas. Utiliza los diferentes ordenamientos de listas libres (`-l ADDRSORT, -l SIZESORT +, -l SIZESORT-`) para observar cómo interactúan las políticas y los ordenamientos de listas. 

### Introducción a la paginación

El programa `paging-lineal.py`, que indica cómo funciona la traducción simple de dirección virtual a física con tablas de páginas lineales. Puedes utiliza el indicador -h para ver todos los argumentos del programa:

```python
python paging-lineal.py -h
```

Lo que el programa  proporciona es una tabla de páginas para un proceso en particular (recuerda, en un sistema real con tablas de páginas lineales, hay una tabla de páginas por proceso. Aquí solo nos enfocamos en un proceso, su espacio de direcciones y, por lo tanto, una tabla de una sola página). La tabla de páginas indica,  que para cada número de página virtual (VPN) del espacio de direcciones, la página virtual está asignada a un número de frame física (PFN) particular y, por lo tanto, es válida o no válida.

El formato de la entrada de la tabla de páginas es simple: el bit más a la izquierda (orden superior) es el bit válido; los bits restantes, si es válido es 1, es el PFN.

En el ejemplo anterior, la tabla de páginas asigna VPN 0 a PFN 0xc (12 decimal), VPN 3 a PFN 0x6 (decimal 6), y deja las otras dos páginas virtuales, 1 y 2, como no válidas.

Como la tabla de páginas es una matriz lineal, lo que se imprime arriba es una réplica de lo que se vería en la memoria si miraras los bits. Sin embargo, a veces es más fácil usar este simulador si se ejecutas con el indicador detallado (-v). Este indicador también imprime el VPN (índice) en la tabla de páginas. 

```pyt
Tabla de paginas (desde la entrada 0 hasta el max size)
  [       0]  0x8000000c
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x80000006
```

Tu trabajo, es utilizar esta tabla de páginas para traducir las direcciones virtuales que se le dieron seguimiento a direcciones físicas. Veamos el primero: VA 0x3229. Para traducir esta dirección virtual en una dirección física, primero tenemos que dividirla en sus componentes constitutivos: un número de página virtual y un offset. Hacemos esto anotando el tamaño del espacio de direcciones y el tamaño de la página. En este ejemplo, el espacio de direcciones se establece en 16 KB (un espacio de direcciones muy pequeño) y el tamaño de la página es de 4KB. Por lo tanto, sabemos que hay 14 bits en la dirección virtual y que el offset es de 12 bits, dejando 2 bits para la VPN. Por lo tanto, con nuestra dirección 0x3229, que es binaria 11 0010 0010 1001, sabemos que los dos bits superiores especifican la VPN. Por lo tanto, 0x3229 está en la página virtual 3 con un offset de 0x229.

A continuación, miramos en la tabla de páginas para ver si VPN 3 es válida y si está asignada a algún marco físico o no es válida, y vemos que sí es válida (por qué?) :

Por lo tanto, podemos formar nuestra dirección física final tomando la página física 6 y agregándola al offset, de la siguiente manera: 0x6000 (la página física, desplazada al lugar apropiado) o  0x0229 (el offset) , produciendo la dirección física final: 0x6229. Por lo tanto, podemos ver que la dirección virtual 0x3229 se traduce en la dirección física 0x6229 en este ejemplo.

Para ver el resto de las soluciones, ejecuta el indicador -c .

Se puede cambiar muchos de estos parámetros para crear problemas más interesantes.

* El indicador -s cambia la semilla aleatoria y, por lo tanto, genera diferentes valores de tabla de páginas, así como diferentes direcciones virtuales para traducir.
* La bandera -a cambia el tamaño del espacio de direcciones.
* El indicador -p cambia el tamaño de la memoria física.
* La bandera -P cambia el tamaño de una página.
* El indicador -n se puede usar para generar más direcciones para traducir (en lugar de las 5 predeterminadas).
* El indicador -u cambia la fracción de mappings que son válidas, desde 0% (-u 0) hasta 100% (-u 100). El valor predeterminado es 50, lo que significa que aproximadamente la mitad de las páginas en el espacio de direcciones virtuales serán válidas.
* El indicador -v imprime los números VPN.

### Ejercicios

1. Antes de realizar cualquier traducción, usemos el simulador para estudiar cómo las tablas de páginas lineales cambian de tamaño dados diferentes parámetros. Calcula el tamaño de las tablas de páginas lineales a medida que cambian los diferentes parámetros. Algunas entradas sugeridas están abajo.  Al usar el indicador `-v`, se puede ver cuántas entradas de tabla de páginas se completan. Primero, para comprender cómo cambia el tamaño lineal de la tabla de páginas a medida que crece el espacio de direcciones se hace:

   ```python
   paging-lineal.py -P 1k -a 1m -p 512m -v -n 0
   paging-lineal-.py -P 1k -a 2m -p 512m -v -n 0
   paging-lineal.py -P 1k -a 4m -p 512m -v -n 0
   ```

   Luego, para comprender cómo cambia el tamaño lineal de la tabla de páginas a medida que crece el tamaño de la página se hace:

   ```python
   paging-lineal.py -P 1k -a 1m -p 512m -v -n 0
   paging-lineal.py -P 2k -a 1m -p 512m -v -n 0
   paging-lineal.py -P 4k -a 1m -p 512m -v -n 0
   ```

   ​	Antes de ejecutar cualquiera de estos segments, trata de pensar en las tendencias esperadas. ¿Cómo 	debería cambiar el tamaño de la tabla de la página medida que crece el espacio de direcciones? A	 	medida que crece el tamaño de la página? ¿Por qué no deberíamos usar páginas realmente grandes  	en general?.

   2 . Ahora hagamos algunas traducciones. Comienza con algunos ejemplos pequeños y cambia el número de páginas que se asignan al espacio de direcciones con el indicador `-u`. Por ejemplo:

   ```python
   paging-lineal.py -P 1k -a 16k -p 32k -v -n 0
   paging-lineal.py -P 1k -a 16k -p 32k -v -n 25
   paging-lineal.py -P 1k -a 16k -p 32k -v -n 50
   paging-lineal.py -P 1k -a 16k -p 32k -v -n 75
   paging-lineal.py -P 1k -a 16k -p 32k -v -n 100
   ```

   ¿Qué sucede cuando aumenta el porcentaje de páginas que se asignan en cada espacio de direcciones?.



### TLB

En estos ejercicios,  debes medir el tamaño y el costo de acceder a un TLB. La idea se basa en el trabajo de Saavedra-Barrera  quien desarrolló un método simple para medir numerosos aspectos de las jerarquías de caché, todo con un programa de nivel de usuario muy simple. 

La idea básica es acceder a cierto número de páginas dentro de una gran estructura de datos (por ejemplo, un array) y cronometrar esos accesos. Por ejemplo, supongamos que el tamaño TLB de una máquina es 4 (que sería muy pequeño, pero útil para los fines de esta discusión). Si escribes un programa que toca 4 páginas o menos, cada acceso debe ser un hit TLB y, por lo tanto, relativamente rápido. Sin embargo, una vez que toca 5 páginas o más, repetidamente en un bucle, cada acceso aumentará repentinamente su costo en un miss TLB.

El código básico para recorrer un array una vez debería verse así:



```python
int jump = PAGESIZE / sizeof(int);
for (i = 0; i < NUMPAGES * jump; i += jump) {
      a[i] += 1;
}
```

En este bucle, se actualiza un número entero por página del array $a$, hasta el número de páginas especificado por NUMPAGES. Al cronometrar dicho ciclo repetidamente (por ejemplo, unos cientos de millones de veces en otro ciclo alrededor de este, o sin importar cuántos ciclos se necesiten para ejecutarse durante unos segundos), puede calcular el tiempo que toma cada acceso (en promedio). Al buscar saltos en el costo a medida que aumenta el NUMPAGES, puedes determinar aproximadamente qué tan grande es el TLB de primer nivel, determinar si existe un TLB de segundo nivel (y qué tan grande es si lo hace), y en general tener una buena idea de cómo los hit y miss de TLB pueden afectar el rendimiento.

La diferencia general entre hit y miss en el TLB de primer nivel es bastante grande, aproximadamente un factor de catorce. 



### Ejercicios



1. Para el tiempo, necesitará usar un temporizador (por ejemplo, `gettimeofday() `. ¿Qué tan preciso es tal temporizador? ¿Cuánto tiempo debe demorar una operación para que pueda cronometrarla con precisión? (esto ayudará a determinar cuántas veces, en un bucle, tendrá que repetir un acceso a la página para cronometrarlo correctamente).
2. Escribe  un programa, llamado `tlb.c`, que puede medir aproximadamente el costo de acceder a cada página. Las entradas al programa deben ser: el número de páginas a tocar y el número de pruebas.
3. Ahora escribe una secuencia de comandos para ejecutar este programa, mientras varía el número de páginas a las que se accede desde 1 hasta unos pocos miles, quizás incrementándose en un factor de dos por iteración. Ejecuta el script en diferentes máquinas y recopila algunos datos. ¿Cuántas pruebas son necesarios para obtener mediciones confiables?
4. Grafica los resultados. La visualización generalmente hace que los datos sean mucho más fáciles de entender. ¿Por qué crees eso?.

### Tablas pequeñas

Supuestos del programa: `paging-multilevel.py`

Algunos supuestos básicos:

* El tamaño de la página es de 32 bytes poco realistas
* El espacio de dirección virtual para el proceso en cuestión (suponga que solo hay uno) es de 1024 páginas, o 32 KB
* La memoria física consta de 128 páginas

Por lo tanto, una dirección virtual necesita 15 bits (5 para el offset, 10 para la VPN). Una dirección física requiere 12 bits (5  offsets, 7 para la PFN).

El sistema asume una tabla de páginas de niveles múltiples. Por lo tanto, los cinco bits superiores de una dirección virtual se utilizan para indexar en un directorio de página. La entrada del directorio de páginas (PDE), si es válida, apunta a una página de la tabla de páginas. Cada página de tabla de páginas contiene 32 entradas de tabla de páginas (PTE). Cada PTE, si es válido, contiene la traducción deseada (PFN) de la página virtual en cuestión.

El formato de un PTE es así:

```bash
VALID | PFN6 ... PFN0
```

y por lo tanto es de 8 bits o 1 byte.

El formato de un PDE es esencialmente idéntico:

  ```bash
VALID | PT6 ... PT0
  ```

Para empezar, se le dan dos piezas de información.

Primero, se le da el valor del registro base del directorio de páginas (PDBR), que le indica en qué página se encuentra el directorio de páginas.

En segundo lugar, se le da un dump completo de cada página de memoria. Un dump de página se ve así:

```bash
page 0: 08 00 01 15 11 1d 1d 1c 01 17 15 14 16 1b 13 0b ...
page 1: 19 05 1e 13 02 16 1e 0c 15 09 06 16 00 19 10 03 ...
page 2: 1d 07 11 1b 12 05 07 1e 09 1a 18 17 16 18 1a 01 ...
...
```

que muestra los 32 bytes encontrados en las páginas 0, 1, 2, etc. El primer byte (byte 0) en la página 0 tiene el valor 0x08, el segundo es 0x00, el tercero 0x01, y así sucesivamente.

Luego se le da una lista de direcciones virtuales para traducir.

Usa el PDBR para encontrar las entradas relevantes de la tabla de páginas para esta página virtual. Entonces encuentra si es válido. Si es así, usa la traducción para formar una dirección física final. Con esta dirección, puede encontrar el VALOR que está buscando la referencia de memoria.

Por supuesto, la dirección virtual puede no ser válida y generar un error.

Algunas opciones útiles:



*  `-s SEED, --seed = SEED` la semilla aleatoria
*  `-n NUM, --addresses = NUM` ​​número de direcciones virtuales para generar
*   `-c, - solve` respuestas de cálculo 

Cambia la semilla para tener diferentes problemas, como siempre.

Cambia el número de direcciones virtuales generadas para hacer más traducciones para un dump de memoria dado.

Usa `-c (o --solve)` para mostrar las soluciones.



### Ejercicios



1. Con una tabla de páginas lineal, necesitas un único registro para ubicar la tabla de páginas, suponiendo que el hardware realiza la búsqueda en caso de error del TLB. ¿Cuántos registros necesitas para ubicar una tabla de página de dos niveles? ¿Una tabla de tres niveles?.
2. Usa el simulador para realizar traducciones, con las semillas aleatorias 0, 1 y 2, y verifica sus respuestas usando la bandera -c. ¿Cuántas referencias de memoria se necesitan para realizar cada búsqueda
3. Dado su conocimiento de cómo funciona la memoria caché, ¿cómo cree que las referencias de memoria a la tabla de páginas se comportarán en la memoria caché? ¿Conducirán a muchos hits de caché (y, por lo tanto, a accesos rápidos) o a muchos errores (y, por lo tanto, accesos lentos)?.





