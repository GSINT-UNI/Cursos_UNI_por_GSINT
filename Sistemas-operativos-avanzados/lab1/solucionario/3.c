#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int f = fork();

    if (f < 0) {
        fprintf(stderr, "fork() failed!\n");
        exit(1);
    } else if (f == 0) {
        fprintf(stdout, "Hola CC-571\n");
    } else {
        sleep(2);
        fprintf(stdout, "a cuidarse\n");
    }

    return 0;
}
