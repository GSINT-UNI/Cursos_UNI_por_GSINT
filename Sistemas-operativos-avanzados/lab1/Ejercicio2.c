#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_CONTEO  200

void  ProcesoHijo(void);      
void  ProcesoPadre(void); 

void  main(void)
{
     pid_t  pid;
     pid = fork();
     if (pid == 0) 
          ProcesoHijo();
     else 
          ProcesoPadre();
}

void  ProcesoHijo(void)
{
     int   i;

     for (i = 1; i <= MAX_CONTEO; i++)
          printf("Esta linea es del hijo, valor = %d\n", i);
     printf("*** El proceso hijo esta completo ***\n");
}

void  ProcesoPadre(void)
{
     int   i;

     for (i = 1; i <= MAX_CONTEO; i++)
          printf("Esta linea es el de padre, valor = %d\n", i);
     printf("***El proceso padre esta hecho***\n");
}
