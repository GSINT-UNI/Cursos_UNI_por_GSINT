#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	int rc = fork();
	int x = 50;
	if(rc < 0){
		fprintf(stderr,"fork ha fallado\n");
		exit(1);
	} else if(rc == 0){
		printf("x original en el proceso hijo es %d\n", x);
		x = 10;
		printf("x cambiado en el proceso hijo es  %d\n",x);
	}
	else{
		x = 20;
		printf("x cambiado en el proceso padre es %d\n",x);
	}
}
