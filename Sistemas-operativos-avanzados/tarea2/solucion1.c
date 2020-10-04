#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int call_execl(char * myargs[]) {
    pid_t p = fork();

    if (p == 0) {
        execl(myargs[0], myargs[1], myargs[2], (char*) NULL);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}
int call_execlp(char * myargs[]) {
    pid_t p = fork();

    if (p == 0) {
        execlp(myargs[0], myargs[1], myargs[2], (char*) NULL);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}
int call_execle(char * myargs[], char * myenv[]) {
    pid_t p = fork();

    if (p == 0) {
        execle(myargs[0], myargs[1], myargs[2], myargs[3], (char *) NULL, myenv);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}
int call_execv(char * myargs[]) {
    pid_t p = fork();

    if (p == 0) {
        execv(myargs[0], myargs + 1);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}
int call_execvp(char * myargs[]) {
    pid_t p = fork();

    if (p == 0) {
        execvp(myargs[0], myargs + 1);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}
int call_execvpe(char * myargs[], char * myenv[]) {
    pid_t p = fork();

    if (p == 0) {
        execvpe(myargs[0], myargs + 1, myenv);
    } else if (p > 0) {
        int w = wait(NULL);
        if (w != -1)
            fprintf(stdout, "[%d]: %d just terminated!\n", getpid(), w);
        else fprintf(stderr, "[%d]: got code %d. Process not found!\n", getpid(), w);
        
    } else {
        fprintf(stderr, "[%d]: fork failed!\n", getpid());
        exit(EXIT_FAILURE);
    }

    return 0;
}


int main(int argc, char * argv[]) {

    char * myarg[] = {"/bin/ls", "superls", "-lhr", (char *) NULL};
    char * myarg_p[] = {"ls", "superduperls", "-lahtr", (char *) NULL};
    char * myenv[] = {"HOME=/etc/passwd", (char*)NULL};

    fprintf(stdout, "Calling execl...\n");
    call_execl(myarg);
    fprintf(stdout, "Calling execlp...\n");
    call_execlp(myarg_p);
    fprintf(stdout, "Calling execle...\n");
    call_execle(myarg, myenv);
    fprintf(stdout, "Calling execv...\n");
    call_execv(myarg);
    fprintf(stdout, "Calling execlp...\n");
    call_execlp(myarg_p);
    fprintf(stdout, "Calling execvpe...\n");
    char * mysuperarg[] ={"bash","superbash", "-c", "cat $HOME", (char *) NULL};
    call_execvpe(mysuperarg, myenv);

    return 0;
} 