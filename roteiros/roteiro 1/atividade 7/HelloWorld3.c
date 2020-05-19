// HelloWorld3.c (Roland Teodorowitsch; 26 ago. 2019)
#include <stdio.h>
int main()
{
    #pragma omp parallel
    {
        int i;
        for (i = 0; i < 10; ++i)
            printf("Hello World from OpenMP\n");
    }
    return 0;
}
