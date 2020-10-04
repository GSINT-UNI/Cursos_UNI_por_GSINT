#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    int * p_null = NULL;
    fprintf(stdout, "%p\n", p_null);
    free(p_null);

    return 0;
}