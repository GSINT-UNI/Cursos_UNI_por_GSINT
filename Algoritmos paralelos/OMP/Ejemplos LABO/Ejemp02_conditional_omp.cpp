#include <iostream>
#include<omp.h>
#define CHUNKSIZE 100
#define N     10

using namespace std;

int main(int argc, char *argv[])
{
int i, chunk;
float a[N], b[N], c[N];
omp_set_num_threads(4);
int TID = omp_get_thread_num();
cout<<"Hilo maestro es "<<TID<<endl;

for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;
#pragma omp parallel shared(a,b,c,chunk) private(i)
  {
  #pragma omp for schedule(dynamic,chunk) nowait
  for (i=0; i < N; i++)
    c[i] = a[i] + b[i];
  }  /* end of parallel section */


for (i=0; i < N; i++)
	cout<<a[i]<<"\t"<<b[i]<<"\t"<<c[i]<<endl;

}
