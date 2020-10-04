#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <math.h>

int main(){
	char leer_buffer[100];
	for(int i=100;i<=1000000;i*=10){	
	struct timespec tiempo1 = {0,0};
	struct timespec tiempo2 = {0,0};
	clock_gettime(CLOCK_REALTIME,&tiempo1);
		for(int j=0;j<i;j++){
			read(STDIN_FILENO,leer_buffer,0);
		}
		clock_gettime(CLOCK_REALTIME,&tiempo2);
		long int tiempo_total = (tiempo2.tv_sec - tiempo1.tv_sec) * pow(10,9) + tiempo2.tv_nsec - tiempo1.tv_nsec;
		printf("%d El tiempo de read() toma  %ld ns,en promedio %ld ns/read() \n",i,tiempo_total,tiempo_total/i);	
	}	
	return 0;
}
