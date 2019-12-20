#include <iostream>
#include <mpi.h>
#include <stdlib.h>
using namespace std;

void merge(int a[], int startIndex, int endIndex)
{
int size = (endIndex - startIndex) + 1;
int *b = new int [size]();
int i = startIndex;
int mid = (startIndex + endIndex)/2;
int k = 0;
int j = mid + 1;

while (k < size)
{   
    if((i<=mid) && (a[i] < a[j]))
        {
        b[k++] = a[i++];
    }
    else
    {
        b[k++] = a[j++];
     }
}

for(k=0; k < size; k++)
{
    a[startIndex+k] = b[k];
}
delete []b;
}



void merge_sort(int iArray[], int startIndex, int endIndex)
{
	int midIndex;

//Check for base case
if (startIndex >= endIndex)
{
   return;
  }   

//First, divide in half
midIndex = (startIndex + endIndex)/2;

//First recursive call 
merge_sort(iArray, startIndex, midIndex);

//Second recursive call 
merge_sort(iArray, midIndex+1, endIndex);
	
 //The merge function
 merge(iArray, startIndex, endIndex);

  }

//The main function
int main(int argc, char *argv[])
{
int N=256;
int iArray[N];
//int iArray[] = {2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,2,5,6,4,7,2,8,3,9,10,3,4,5,6,3,2,2,4,5,5,6,5,3,2,4,5,6,7,8,8,2,3,1,4,3,5,3,2,2,5,9,7,5,3,2,4,5,6,7,8,3,4,3,2,2,3,5,2,5,1,4,5,7,8,3,5};
int  j;
for(j=0;j<N;j++) {
	iArray[j]=2*j;
}
cout<<endl;
 /********** inicializar MPI **********/
 int world_rank;
 int world_size;

 MPI_Init(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
 MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        /********** dividir el array en sub-arrays equivalente **************/
if(world_rank == 0) {
 for(j=0;j<N;j++) {
cout<<iArray[j]<<" "; 
}
cout<<endl;
}
int size = N/world_size;
//int *sub_array = malloc(size * sizeof(int));
int sub_array[size];

MPI_Scatter(iArray, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);

//merge_sort(iArray, 0, 99);
merge_sort(sub_array, 0, size-1);

int sorted[size];
MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);

if(world_rank == 0) {
	merge_sort(sorted, 0, N-1);

//Print the sorted array
for(int i=0; i < N; i++)
{
    cout << sorted[i] << endl;
    }
}
        /********** Finalize MPI **********/
MPI_Barrier(MPI_COMM_WORLD);
MPI_Finalize();

    return 0;    
    }
