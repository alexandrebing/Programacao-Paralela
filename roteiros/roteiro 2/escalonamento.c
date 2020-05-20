// escalonamento.c (Roland Teodorowitsch; 5 de set. 2019)
#include <stdio.h>
#include <omp.h>
#define TAM 32
int main()
{
    int i;
    omp_set_num_threads(4);
#pragma omp parallel for
    for (i = 0; i < TAM; i++)
        printf("Thread %d processando iteracao %d\n", omp_get_thread_num(), i);
    return 0;
}