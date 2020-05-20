// HelloWorld4.c (Roland Teodorowitsch; 26 ago. 2019)
#include <stdio.h>
int main()
{
    int i;
    #pragma omp parallel for
    for (i = 0; i < 10; ++i)
        printf("Hello World from OpenMP\n");
    return 0;
}
