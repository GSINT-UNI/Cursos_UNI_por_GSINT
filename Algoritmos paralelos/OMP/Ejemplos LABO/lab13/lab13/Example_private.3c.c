/*
* @@name:	private.3c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include <assert.h>
#include <stdio.h>
#include <omp.h>

void priv_example3()
{
  int i, a;

  #pragma omp parallel private(a)
  {
     a = 1;
    #pragma omp parallel for private(a)
      for (i=0; i<10; i++)
     {
       a = 2;
     }
      printf("a: %d\n",a);
//    assert(a == 1);
  }
}

int main(){
priv_example3();
}
