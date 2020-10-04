# Respuesta 2

## shell
Para que la salida se realice a través de un fichero, se puede modificar el código
de la siguiente manera:
```c
comando = leer_usuario();
int rc = fork();
if(rc == 0) { //proceso hijo
    close(STDOUT_FILENO);
    int fd = open(
        "./output",
        O_WRONLY | O_CREAT | O_APPEND,
        S_IRWXU | S_ISUID | S_IRWXG | S_ISGID
    );
    exec(command);
}
else {// proceso padre
    wait(NULL);
}
```
Primero se cierra la salida estandar y luego se abre un descriptor, que tomará 
el primer identificador libre. Este será 1. Así, la salida del programa escribirá 
en 1 creyendo que es la salida estandar pero es, en realidad, el fichero.

## Cerrando descriptores.

```c
int a = 5;
int fd = open(...) //abriendo un archivo
int ret = fork();
if(ret >0){
    close(fd);
    a = 6;
    ...
}
else if(ret==0){
    printf("a=%d\n", a);
    read(fd, texto);
}
```
Cada vez que ocurre una llamada a `fork`, se crea una copia de la imagen del padre 
en el proceso hijo. Este proceso hijo tendrá una copia en un sector de memoria 
real diferente a la del padre.
Con las suposiciones mencionadas y lo aclarado en el texto anterior, tendremos: 
+ El hijo seguirá teniendo `a = 5` e imprimirá ese valor.
+ El hijo tendrá acceso al descriptor de fichero `fd` puesto que el padre desreferenció 
su copia del descriptor. La _descripción_ sigue vigente y el hijo tiene su propia 
copia del descriptor que lo referencia y esta sigue activa. Por lo tanto, podrá 
operar en ella hasta que decida cerrarla.