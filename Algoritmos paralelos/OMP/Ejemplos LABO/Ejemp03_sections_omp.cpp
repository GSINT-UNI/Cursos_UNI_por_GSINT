#include <omp.h>
#include<iostream>
using namespace std;
#define N     1000

int main()
{ 
int i;
float a[N], b[N], c[N], d[N];
/* Some initializations */
for (i=0; i < N; i++) {
  a[i] = i * 1;
  b[i] = i + 2;  }

#pragma omp parallel shared(a,b,c,d) private(i)
  {
  #pragma omp sections nowait
    {
    #pragma omp section
    for (i=0; i < N; i++)
      c[i] = a[i] + b[i];
    #pragma omp section
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
    }  /* end of sections */
  }  /* end of parallel section */

for (i=0; i < N; i++)
	cout<<a[i]<<"\t"<<b[i]<<"\t"<<c[i]<<"\t"<<d[i]<<endl;

}

