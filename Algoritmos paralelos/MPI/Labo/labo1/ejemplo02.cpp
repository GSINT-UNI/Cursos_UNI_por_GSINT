#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int origen,destino,rank,size,number;

	MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank == 0) {
 // If we are rank 0, set the number to -1 and send it to process 1
    number = -1;
    destino=1;
    MPI_Send(&number, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
    cout<<"Envio de entero "<<number<<" del proceso "<<rank<<endl;
    }
    	else if (rank == 1) {
	origen=0;
    MPI_Recv(&number, 1, MPI_INT, origen, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout<<"Recibo de entero "<<number<<" por el proceso "<<rank<<endl;
    }
	else {
	cout<<"Proceso "<<rank<<" no realiza comunicacion"<<endl;
	}
    MPI_Finalize();
}
