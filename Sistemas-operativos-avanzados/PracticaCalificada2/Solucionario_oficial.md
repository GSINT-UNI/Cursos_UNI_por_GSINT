### Solucionario de la Segunda Práctica Calificada CC-571A 



#### Problema 1

Respuesta: El programa podría maximizar el tiempo de la CPU asignado el no utilizar completamente sus cantidades de cuantos. Se podría usar una  fracción de esa cantidad asignada, pero de manera que se pueda ceder la CPU antes del final del cuanto, aumentando así la prioridad asociada con el proceso.

Para round-robin, es bueno responder que no existe una estrategia. Una posible respuesta sería dividir un proceso en muchos procesos más pequeños y despachar cada uno para que sea iniciado y programado por el sistema operativo.

#### Problema 2

Respuesta: (a) El tamaño del PT disminuye (menos entradas) (b) La tasa de  TLB  hit aumenta (más cobertura) (c) La fragmentación interna aumenta (más espacio desperdiciado en una página).

#### Problema 3

Respuesta: 

(a) La utilización de la CPU aumenta si se minimizan los costos generales asociados con el cambio de contexto. Los costos generales de cambio de contexto podrían reducirse realizando cambios de contexto con poca frecuencia. Sin embargo, esto podría resultar en un aumento del tiempo de respuesta para los procesos.

(b) El tiempo de entrega promedio (TAT) se minimiza ejecutando primero las tareas más cortas. Sin embargo, una política de planificación de este tipo podría privar a las tareas de larga duración y, por lo tanto, aumentar su tiempo de espera.

(c) La utilización de la CPU se maximiza al ejecutar tareas vinculadas a la CPU de larga duración sin realizar cambios de contexto. La utilización de dispositivos de E/S se maximiza programando trabajos vinculados a la E/S tan pronto como estén listos para ejecutarse, incurriendo así en los costos generales de los cambios de contexto.

#### Problema 4

Respuesta:

(a) 770 = 512 + 256 + 2 = 00000011 00000010 = página 3, offset 2

(b) la página 3 se asigna al marco 1. dirección física = 0000001 00000010 = 256 + 2 = 258.

#### Problema 5

Respuesta: Un asignador slab es rápido porque la memoria está preasignada. Además, evita la fragmentación de la memoria del kernel.

#### Problema 6

Respuesta:

(a) Para direcciones virtuales de 6 bits y  offsets de página de 4 bits (tamaño de página de 16 bytes), los 2 bits más significativos de una dirección virtual representarán el número de página. Entonces la cadena de referencia es 0, 0, 1, 0, 1, 1, 2, 1, 0, 3 (repetida nuevamente).

(b) Fallos de página con FIFO = 8. Fallos de página en 0,1,2,3 (reemplazado 0), 0 (reemplazado 1), 1 (reemplazado2), 2 (reemplazado 3), 3.

(c) Fallos de página con LRU = 6. Fallos de página en 0, 1, 2, 3 (reemplazado 2), 2 (reemplazado 3), 3.

(d) El algoritmo óptimo reemplazará la página con menos probabilidades de ser utilizada en el futuro, y se vería como el LRU arriba.

#### Problema 7

Respuesta:

(a) [512 B] [256 B] 256 B libre [1024 B] [2048 B]

(b) [512 B] 512 B libre, 1024 B libre, 2048 B libre. No es posible un mayor coalescing.

#### Problema 8

Respuesta:

(a) 7 = 0000 (número de página) + 0111 (offset) = página lógica 0.  TLB miss . No hay recorrido de la tabla de página. No hay trap del sistema operativo. Se accede a la dirección física 0110 0111.

(b) 20 = 0001 0100 = página lógica 1. TLB miss. El MMU recorre la tabla de la página. Dirección física 0011 0100

(c) 70 = 0100 0110 = página lógica 4. TLB miss . MMU accede a la tabla de páginas y descubre que es una entrada no válida. MMU genera un trap en el sistema operativo. 

(d) 80 = 0101 0000 = página lógica 5. TLB miss. MMU accede a la tabla de páginas y descubre que la página no está presente. MMU genera un error de página en el sistema operativo.

#### Problema 9

Respuesta: 

(a) Aquí debes explicar que  *a*  completa en una unidad de tiempo 55 (10 + 90/2), *b* y *c* se calientan en caché en una unidad de tiempo 20, por lo que b y c se completan en la unidad de tiempo 110(20 + 90/2 * 2). Esta es la combinación más rápida.

(b) Ejecutar y analizar todas las posibles combinaciones:

```python
python multi.py -n 1 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 50 -c -t -T -C 
python multi.py -n 2 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 50 -c -t -T -C 
python multi.py -n 3 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 50 -c -t -T -C 

python multi.py -n 1 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 100 -c -t -T -C 

python multi.py -n 2 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 100 -c -t -T -C 

python multi.py -n 3 -L a: 100: 100, b: 100: 100, c: 100: 100 -M 100 -c -t -T -C 

```

Se demuestra la aceleración superlineal con cambios en el tiempo de finalización a medida que se utilizan con múltiples CPU y sus cachés.

#### Problema 10

Respuesta: 0 (el  acierto del TLB implica que se ha asignado una página física, por lo que no se puede producir un error de página).