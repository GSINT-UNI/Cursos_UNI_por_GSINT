#include <iostream>
#include <omp.h>
using namespace std;

int main ()  
{
   int nthreads = 8,id;
   omp_set_num_threads(nthreads);

   #pragma omp parallel private(id)   
   {
      id = omp_get_thread_num();

	//#pragma omp barrier
      cout<<"Saludos desde el hilo = "<<id<<" con "<<omp_get_num_threads()<<" hilos"<<endl;

//  	if (id == 0) 
  //	{
	nthreads = omp_get_num_threads();
//	cout<<"Cantidad de hilos = "<<nthreads<<endl;
    // 	}
   }
   cout<<"Listo!, trabajado con "<< nthreads<<" hilos"<<endl;;

}

 

