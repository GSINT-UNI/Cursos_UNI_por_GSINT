#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_CONTEO  200
#define   TAM_BUFFER   100

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[TAM_BUFFER];

     fork();
     pid = getpid();
     for (i = 1; i <= MAX_CONTEO; i++) {
          sprintf(buf, "Esta linea es de pid %d, valor = %d\n", pid, i);
          write(1, buf, strlen(buf));
     } 
}
