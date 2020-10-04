#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[]) {

    int p = fork();

    if (p == 0) {
        printf("[%d]: Hello, friend!.\n", getpid());
        close(STDOUT_FILENO);
        printf("[%d]: I'm trying to tell you something, friend...\n", getpid());
    } else if (p > 0) {
        wait(NULL);
        fprintf(stdout, "[%d]: Good bye, friend!\n", getpid());
    } else
    {
        fprintf(stderr, "[%d]: forked failed\n", getpid());
    }
    

    return 0;
}