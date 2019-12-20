/*
* @@name:	ordered.2c
* @@type:	C
* @@compilable:	no
* @@linkable:	no
* @@expect:	failure
*/
#include<stdio.h>
#include<omp.h>

void work(int i) {printf("i: %d\n",i);}

void ordered_wrong(int n)
{
  int i;
  #pragma omp for ordered
  for (i=0; i<n; i++) {
/* incorrect because an iteration may not execute more than one
   ordered region */
    #pragma omp ordered
      work(i);
    #pragma omp ordered
      work(i+1);
  }
}

int main(){
	int n=10;
ordered_wrong(n);
}
