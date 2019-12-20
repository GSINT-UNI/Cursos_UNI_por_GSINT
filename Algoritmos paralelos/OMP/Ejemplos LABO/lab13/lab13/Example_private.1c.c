/*
* @@name:	private.1c
* @@type:	C
* @@compilable:	yes
* @@linkable:	yes
* @@expect:	success
*/
#include <stdio.h>
#include <assert.h>

int main()
{
  int i, j;
  int *ptr_i, *ptr_j;

  i = 1;
  j = 2;

  ptr_i = &i;
  ptr_j = &j;

  #pragma omp parallel private(i) firstprivate(j)
  //#pragma omp parallel private(i,j) 
//  #pragma omp parallel  
  {
    i = 3;
    j = j + 2;
#pragma omp single
  printf("parallel i: %i j: %i \n",i,j);
    assert (*ptr_i == 1 && *ptr_j == 2);
  }

  //assert(i == 1 && j == 2);
  printf("i: %i j: %i \n",i,j);

  return 0;
}
