#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#define num_iteraciones 1000000

int main(int argc, char *argv[]) {
    // medida de llamada al sistema
    int fd = open("f.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    struct timeval tiempo1, tiempo2;
    gettimeofday(&tiempo1, NULL);
    for (size_t i = 0; i < num_iteraciones; i++) {
        read(fd, NULL, 0);
    }
    gettimeofday(&tiempo2, NULL);
    printf("Llamada al sistema: %f microsegundos\n\n",(float)(tiempo2.tv_sec * 1000000 + tiempo2.tv_usec - tiempo1.tv_sec * 1000000- 
    		tiempo1.tv_usec)/ num_iteraciones);
    close(fd);

    // medida de cambio de contexto
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    int pipe1fd[2], pipe2fd[2];
    if (pipe(pipe1fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe2fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) { //proceso hijo
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < num_iteraciones; i++) {
            read(pipe1fd[0], NULL, 0);
            write(pipe2fd[1], NULL, 0);
        }
    } else { // proceso padre
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }

        gettimeofday(&tiempo1, NULL);
        for (size_t i = 0; i < num_iteraciones; i++) {
            write(pipe1fd[1], NULL, 0);
            read(pipe2fd[0], NULL, 0);
        }
        gettimeofday(&tiempo2, NULL);
        printf("Cambio de contexto en : %f microsegundos\n", (float) (tiempo2.tv_sec * 1000000 + tiempo2.tv_usec - tiempo1.tv_sec * 1000000 -  			tiempo1.tv_usec) / num_iteraciones);
    }
    return 0;
}
