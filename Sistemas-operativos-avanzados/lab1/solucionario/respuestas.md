# Respuestas Lab01
## Respuesta 1
### programa1
`fork()` crea un proceso hijo y continúa la ejecución del resto del programa. 
Se puede observar que ambos procesos(padre e hijo) realizan el mismo bucle
y llegan al mismo número(200) y se puede observar que corren concurrentemente.

### programa2
`fork()` crea un proceso hijo y, según el valor de retorno, que difiere en hijo 
y en padre, se determina por un bucle en particular.

## Respuesta 2
La variable se modifica pero esta modificación solo es visible en el entorno
hijo o padre. Es decir, el padre no sabe que el hijo modifico la variable y 
viceversa.

## Respuesta 3
Se puede implemetar una pseudo solución otorgandole un retardo de unos 
segundos al padre utilizando `sleep(n)`. Sin embargo, en una condición 
particular, esto no podría funcionar.

## Respuesta 4
El valor de retorno de `wait()` es el pid del hijo que fue 'segado'. 
Al usar `wait()` en el hijo, este arroja un código `-1` que es el código 
de error.

## Respuesta 5
Con `waitpid()` tenemos la ventaja de que el hijo segado es justo el 
hijo del pid que nosotros queremos.