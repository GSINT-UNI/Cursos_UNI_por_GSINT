# Examen Final - solucionario no oficial


### Un algoritmo de reemplazo de página de reloj intenta aproximarse a un algoritmo de uso menos reciente (LRU).

En un caso particular, sí. Pensando en la lista de páginas como una lista circular, pues tendremos que, sí encuentra una página marcada como **no usada**, entonces es muy probable que ya se haya recorrido toda la lista y la página no haya sido usada en un tiempo menor que _las que quedan_.

### El sistema de archivos ext4 de Linux se diferencia de ext3 en que utiliza...

Asignación de bloque en bloque(en la alternativa, _cluster_). La ventaja de ext4 es que evita en gran medida la fragmentación del disco.

### Los algoritmos de planificación de disco intentan minimizar los efectos de...

Discrepo un poco con las alternativas. Diferentes algoritmos están enfocados de forma diferente a minimizar un _tipo de tiempo_ en particular. De todas formas, escojo **tiempo de búsqueda** porque es el que depende más del algoritmo. No se puede modificar la rapidez de transferencia y la latencia rotacional suele ser despreciable.

### ¿Qué forma de journaling tiene el menor riesgo de corrupción de datos?

El _journaling físico_. 

### Los locks se pueden implementar aprovechando las interrupciones en computadoras con un solo procesador

No estoy seguro, pero se tenía que escoger algo...

### El algoritmo Shortest Seek Time First (SSTF) tiene el peligro de hacer starving en algunas solicitudes.

Recuerde, nada más, el _efecto convoy_.

### El thrashing en un sistema de memoria virtual es causado por...

... el _thrashing_ se define como la intensa carga de memoria(usualmente paginación) desproporcionada para con el trabajo útil que se realiza. Puede ocurrir por múltiples razones: mal algoritmo de paginación, mala programación de un proceso(al solicitar información que no usa), múltiples pedidos a la memoria de diferentes procesos, o incluso un mal diseño del sistema de ficheros.

### En los sistemas POSIX, un dispositivo se identifica dentro del sistema de archivos mediante...

un fichero que requiere una entrada _i-nodo_, pero que es un tipo especial de fichero. 

### Si el algoritmo del banquero encuentra que es seguro asignar un recurso a un hilo existente, todos los hilos eventualmente se completarán.

Nunca confié en el algoritmo del banquero. Seguro fue una broma de Dijkstra...

### Los hilos dentro del mismo proceso pueden compartir datos entre sí pasando punteros a objetos en sus pilas.

Sí. Así está implementado _pthreads_.