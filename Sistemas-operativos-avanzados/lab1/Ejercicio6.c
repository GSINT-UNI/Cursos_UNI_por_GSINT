#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork a fallado\n" );
	}
	else if(rc == 0){
		printf("Ejecutando el proceso hijo (%d)\n", (int)getpid());
	}
	else{
		int wc = waitpid(rc,NULL,0);
		printf("El proceso padre es informado que el proceso hijo (%d) ha terminado\n", wc);
	}
	return 0;
}
