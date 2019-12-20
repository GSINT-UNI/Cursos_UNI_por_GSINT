/************************************************************************
 * Solucion modelo del ejercicio 3 del examen parcial
 * de Algoritmos Paralelos (2015-I)
 ************************************************************************/

#include        <stdio.h>
#include        "mpi.h"
#define to_right 201
#define to_left  102

int main (int argc, char *argv[])
{
  int ierror, rank, my_rank, size;
  int right, left;
  int other, usuarios, sum, i;
  
  MPI_Status  send_status;
  MPI_Status  recv_status;
  MPI_Request request;
  
  ierror = MPI_Init(&argc, &argv);
  
  ierror = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  ierror = MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  right = my_rank + 1;
  if (right == size) right = 0;
  
  left = my_rank - 1;
  if (left == -1) left = size-1;
  
  sum = 0;
  rank = my_rank;
  usuarios=1000+100*rank;
  //usuarios=rank;

  for( i = 0; i < size; i++) {
    
    ierror = MPI_Send(&usuarios, 1, MPI_INT, right, to_right, MPI_COMM_WORLD);
    
    ierror = MPI_Recv(&other, 1, MPI_INT, left, to_right, MPI_COMM_WORLD, &recv_status);
    
    sum = sum + other;
    //sum = sum + usuarios;
    printf("rank %i usuarios: %i sum: %i \n",rank,usuarios,sum);
    usuarios = other;
  }
  
  printf ("PE%d:\tSum = %d\n", usuarios, sum);
  
  ierror = MPI_Finalize();
  return 0;
}
