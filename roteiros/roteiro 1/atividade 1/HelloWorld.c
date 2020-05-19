#include <stdio.h>

int main () {
	#pragma omp parallel
	printf("Hello World from OpenMP\n");
	return 0;
}
