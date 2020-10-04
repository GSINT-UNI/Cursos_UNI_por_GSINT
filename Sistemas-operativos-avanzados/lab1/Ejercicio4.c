#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
int main(){
	int fd[2];
	pipe(fd); // https://www.geeksforgeeks.org/pipe-system-call/
	int rc = fork();
	char leer_buffer[80];
	if(rc < 0){
		fprintf(stderr, "fork a fallado\n");
	}
	else if(rc == 0){
		close(fd[0]);
		printf("Proceso hijo:Hola CC-571\n");
		char mensaje[] = "a cuidarse";
		write(fd[1],mensaje,strlen(mensaje));
	}
	else{
		close(fd[1]);
		read(fd[0],leer_buffer,sizeof(leer_buffer));
		printf("Proceso padre:%s\n", leer_buffer);
	}
}
