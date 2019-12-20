/*  MPI_Reduce 
 */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
    	int   me, numprocs;
	int data,res;
	
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(me==0) data = 5.;

    MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
        
	MPI_Reduce(&data, &res, 1, MPI_INT, MPI_SUM,
	                   0, MPI_COMM_WORLD);

	if (me==0) {
		cout<<"Proceso "<<me<<", res: "<<res<<endl;
        }
    
    MPI_Finalize();
}
    
