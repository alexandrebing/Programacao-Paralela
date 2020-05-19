// HelloWorld2.c (Roland Teodorowitsch; 26 ago. 2019)
#include <omp.h>
#include <stdio.h>
int main()
{
    #pragma omp parallel
    {
        int id, numThreads;
        id = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        printf("Hello World from thread %d (of %d)\n", id, numThreads);
    }
    return 0;
}
