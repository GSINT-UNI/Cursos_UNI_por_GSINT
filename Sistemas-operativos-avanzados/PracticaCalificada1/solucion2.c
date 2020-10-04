#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_STDINPUT_LENGTH 1024
#define MAX_ARG_NUM 64

char * trimstr(char * str) {
    int len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = '\0';
    return str;
}

char ** splitcommand(char * buffer) {
    char * part = strtok(buffer, " ");
    char ** splitted = malloc(sizeof(char *) * MAX_ARG_NUM);

    if (splitted == NULL) {
        fprintf(stderr, "No memory!!\n");
    }
    int pos = 0;

    while (part != NULL) {
        *(splitted + pos) = part;
        part = strtok(NULL, " ");
        pos++;
    }

    *(splitted + pos - 1) = trimstr(*(splitted + pos - 1));
    *(splitted + pos) = NULL;

    return splitted;
}

char ** leer_usuario() {
    char * buffer = malloc(sizeof(char) * MAX_STDINPUT_LENGTH);
    fgets(buffer, MAX_STDINPUT_LENGTH, stdin);
    char ** commandv = splitcommand(buffer);

    return commandv;
}

int main (int argc, char * argv[]) {
    printf("shittyshell> ");
    char ** command = leer_usuario();
    int rc = fork();

    if (rc == 0) { //proceso hijo
        int pos = 0;
        close(STDOUT_FILENO);
        int fd = open(
            "./output",
            O_WRONLY | O_CREAT | O_APPEND,
            S_IRWXU | S_ISUID | S_IRWXG | S_ISGID
        );
        execvp(command[0], command);
    }
    else {// proceso padre
        wait(NULL);
        printf("Exiting\n");
    }

    return 0;
}