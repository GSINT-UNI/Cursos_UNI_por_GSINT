#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    int f = fork();

    if (f < 0) {
        fprintf(stderr, "fork() failed!\n");
        exit(1);
    } else if (f == 0) {
        fprintf(stdout, "[%d]: Hola CC-571\n", getpid());
        int wp = wait(NULL);
        printf("[%d]: wp = %d\n", getpid(), wp);
    } else {
        int wo = wait(NULL);
        fprintf(stdout, "[%d]: a cuidarse\n", getpid());
        printf("[%d]: wo = %d\n", getpid(), wo);
    }

    return 0;
}
