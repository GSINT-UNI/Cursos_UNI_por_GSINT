/*
* @@name:	private.2c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include<stdio.h>
#include<omp.h>

int a;

void g(int k) {
  a = k; /* Accessed in the region but outside of the construct;
          * therefore unspecified whether original or private list
          * item is modified. */
  printf("a: %d\n",a);
}

void f(int n) {
  int i,a = 0;

  #pragma omp parallel for private(a)
   for (i=2; i<n/2; i++) {
       a = i;
       g(a*2);     /* Private copy of "a" */
    }
}

int main(){
int n=1000;
f(n);
}

