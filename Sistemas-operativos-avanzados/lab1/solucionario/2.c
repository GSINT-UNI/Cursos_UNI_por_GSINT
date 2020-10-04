#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    int x = 50;
    fprintf(stdout, "[%d]: x = %d\n", getpid(), x);

    int f = fork();

    if (f < 0) {
        fprintf(stderr, "fork() failed");
        exit(1);
    } else if (f == 0) {
        fprintf(stdout, "[%d]: x = %d\n", getpid(), x);
        x = 249;
        fprintf(stdout, "[%d]: x = %d\n", getpid(), x);
    } else {
        x = 1234123;
        fprintf(stdout, "[%d]: x = %d\n", getpid(), x);
    }

    return 0;
}
