#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void superwriter(int fd, const char * s) {
    int i;

    for (i = 0; i < 100; i++)
        dprintf(fd, s);
    
}

int main(int argc, char * argv[]) {
    char * filename = "output2.out";
    int fd = open(
        filename,
        O_WRONLY | O_CREAT | O_APPEND,
        S_IRWXU | S_ISUID | S_IRWXG | S_ISGID
    );
    fprintf(stdout, "[%d]: file descriptor id = %d\n", getpid(), fd);

    if (fd == -1)  {
        fprintf(stderr, "[%d]: cannot open file descriptor.\n", getpid());
        exit(EXIT_FAILURE);
    } else {
        pid_t p = fork();

        if (p == 0) {
            dprintf(fd, "[%d]: I'm the child.\n", getpid());
            superwriter(fd, "child!");
            close(fd);
        } else if (p > 0) {
            dprintf(fd, "[%d]: I'm the father.\n", getpid());
            superwriter(fd, "father!");
            close(fd);
        } else {
            fprintf(stderr, "[%d]: fork failed!\n", getpid());
        }
    }
    

    return 0;
}