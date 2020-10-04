

# Laboratorio 6

## Concurrencia

1. Examinemos un programa simple, **loop.s**. Ejecuta el programa con estos argumentos `( python x86.py -p loop.s -t 1 -i 100 -R dx)` Esto especifica un solo hilo, una interrupción cada 100 instrucciones y el rastreo del registro `% dx`. ¿Qué será `%dx` durante la ejecución? Usa el indicador  `-c` para verificar sus respuestas.

  Examinando el código:
```asm
.main
.top
sub  $1,%dx
test $0,%dx     
jgte .top
halt
```
Como los registros inician en 0, entonces el valor de `dx` debería decrementar en uno, o sea, tendría valor `-1` y luego el programa terminaría. No entra al loop porque -1 no es mayor o igual que 0.

```
ASSIGN LABEL .main --> 1000
ASSIGN LABEL .top --> 1000

pc:1000 LOADING          sub  $1,%dx --> self.sub_i_to_r(1, 4)
pc:1001 LOADING          test $0,%dx --> self.test_i_r(0, 4)
pc:1002 LOADING            jgte .top --> self.jump_greaterthanorequal(1000)
pc:1003 LOADING                 halt --> self.halt()

   dx          Thread 0         
    0   
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt

```



Efectivamente, esto ocurre.


2. Usemos el mismo código, diferentes indicadores: `( python x86.py -p loop.s -t 2 -i 100 -a dx = 3, dx = 3 -R dx)`.  Esto especifica dos hilos e inicializa cada `%dx` a `3`. ¿Qué  valores  verá `% dx`? Ejecuta el indicacor  `-c` para comprobar. ¿La presencia de varios hilos afecta los cálculos?. ¿Hay una carrera en este código?.

   Pues, esta vez el registro dx almacenará 3. Así, para cada hilo, este valor irá decrementando en el loop .top hasta que tenga valor -1. Entonces, ocurrirá un halt. La presencia de hilos no afecta los cálculos porque el tiempo de interrupción es muy largo.

   ```
   ASSIGN LABEL .main --> 1000
   ASSIGN LABEL .top --> 1000
   
   pc:1000 LOADING          sub  $1,%dx --> self.sub_i_to_r(1, 4)
   pc:1001 LOADING          test $0,%dx --> self.test_i_r(0, 4)
   pc:1002 LOADING            jgte .top --> self.jump_greaterthanorequal(1000)
   pc:1003 LOADING                 halt --> self.halt()
   
      dx          Thread 0                Thread 1         
       3   
       2   1000 sub  $1,%dx
       2   1001 test $0,%dx
       2   1002 jgte .top
       1   1000 sub  $1,%dx
       1   1001 test $0,%dx
       1   1002 jgte .top
       0   1000 sub  $1,%dx
       0   1001 test $0,%dx
       0   1002 jgte .top
      -1   1000 sub  $1,%dx
      -1   1001 test $0,%dx
      -1   1002 jgte .top
      -1   1003 halt
       3   ----- Halt;Switch -----  ----- Halt;Switch -----  
       2                            1000 sub  $1,%dx
       2                            1001 test $0,%dx
       2                            1002 jgte .top
       1                            1000 sub  $1,%dx
       1                            1001 test $0,%dx
       1                            1002 jgte .top
       0                            1000 sub  $1,%dx
       0                            1001 test $0,%dx
       0                            1002 jgte .top
      -1                            1000 sub  $1,%dx
      -1                            1001 test $0,%dx
      -1                            1002 jgte .top
      -1                            1003 halt
   
   ```

   

3. Ejecuta esto:  `python x86.py -p loop.s -t 2 -i 3 -r -a dx = 3, dx = 3 -R dx`.  Esto hace que el intervalo de interrupción sea pequeño/aleatorio. Usa diferentes semillas `(-s)` para ver diferentes intercalaciones. ¿Cambia algo la frecuencia de interrupción?.

   Sí, la frecuencia de interrupción cambia con cada semilla. Sin embargo, esta no supera la cota máxima de tres instrucciones.

4. Ahora, un programa diferente, `looping-race-nolock.s`, que accede a una variable compartida ubicada en la dirección `2000`. Llamaremos a esta variable *value*. Ejecuta con un solo hilo para confirmar su comprensión: `python x86.py -p looping-race-nolock.s -t 1 -M 2000`. ¿Cuál es el valor (es decir, en la dirección de memoria 2000) durante la ejecución?.  Usa `-c` para verificar.

   ```asm
   
   # assumes %bx has loop count in it
   
   .main
   .top	
   # critical section
   mov 2000, %ax  # get 'value' at address 2000
   add $1, %ax    # increment it
   mov %ax, 2000  # store it back
   
   # see if we're still looping
   sub  $1, %bx
   test $0, %bx
   jgt .top	
   
   halt
   
   ```

   Como no se ha especificado nada, en el registro 2000 debería estar almacenado 0. Luego, la agrega uno a qudando su valor en 1. Luego se suma 1 al valor almacenado en bx, que debería ser 0. El salto a .top ocurre solo si 0 es mayor que el valor de bx. Así, el programa no salta bajo la instrucción que nos han dado.

   Probemos algo diferente:

   ```shell
   python x86.py -p looping-race-nolock.s -i 3 -r -t 2 -a bx=10 -M 2000 -R bx -cv
   ```

   
