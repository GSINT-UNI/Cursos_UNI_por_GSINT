#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork a fallado\n");
	}
	else if(rc == 0){
		int wc = wait(NULL);
		printf("wait() devuelve %d en el proceso hijo\n",wc);
	}
	else{
		int wc = wait(NULL);
		printf("wait() devuelve %d en el proceso padre\n",wc);
	}
	return 0;
}
