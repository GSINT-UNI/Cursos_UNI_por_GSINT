#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int rank,size,number;

	MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

//	number=-1; // toda operacion (asignar un valor en la region en paralelo sucede en todos los procesos 

	if (rank == 0) {
    number = -1;
    for (int i=1;i<size;i++){
    MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    //cout<<"Envio de entero "<<number<<" del proceso "<<rank<<" al proceso "<<i<<endl;
    	}
	}
    	else{
    MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //cout<<"Recibo de entero "<<number<<" por el proceso "<<rank<<endl;
    }

    cout<<"Valor de entero "<<number<<" en el proceso "<<rank<<endl;

    MPI_Finalize();
}
