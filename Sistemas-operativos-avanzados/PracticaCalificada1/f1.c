#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define num_iteraciones 1000000
#define VALOR 1000000000L

int main()
{
    struct timespec tiempo1, tiempo2;
    long sum = 0;
    double promedio;

    for (int i = 0; i < num_iteraciones; i++)
    {
        clock_gettime(CLOCK_BOOTTIME, &tiempo1);

        write(fileno(stdout), NULL, 0);

        clock_gettime(CLOCK_BOOTTIME, &tiempo2);
        long diferencia = VALOR * (tiempo2.tv_sec - tiempo1.tv_sec) + tiempo2.tv_nsec - tiempo1.tv_nsec;
        sum += diferencia;
    }
    promedio = sum / (float)num_iteraciones;
    printf("El tiempo promedio de  syscall es %f nano-segundos.\n", promedio);
    return 0;
}
