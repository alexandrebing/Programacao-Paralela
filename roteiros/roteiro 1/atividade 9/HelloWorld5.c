// HelloWorld5.c (Roland Teodorowitsch; 26 ago. 2019)
#include <stdio.h>
#include <omp.h>()
int main()
{
    int i;
    #pragma omp parallel for
    for (i = 0; i < 40; ++i)
    {
        int id, numThreads;
        id = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        printf("Hello World from iteration %d on thread %d (of %d)\n", i, id, numThreads);
    }
    return 0;
}