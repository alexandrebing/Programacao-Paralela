#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

#define NPOINTS 2000
#define MAXITER 2000

struct complex
{
    double real;
    double imag;
};

int getNumOutside();

int main()
{

    int id, p, hs;
    char h[MPI_MAX_PROCESSOR_NAME];

    int numoutside = 0;
    double area, error;
    double start, finish;

    /*
 *   
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

    start = omp_get_wtime();

    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(h, &hs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    for (NPOINTS = 500; NPOINTS <= 5000; NPOINTS += 500)
    {
        numoutside = getNumOutside(NPOINTS);
    }
    MPI_Reduce(&sol, &total, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);
    printf("Process %d on %s is done\n", id, h);
    fflush(stdout);
    MPI_Finalize();
    if (id == 0)
    {
        finish = omp_get_wtime();

        /*
 *  Calculate area and error and output the results
 */

        area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
        error = area / (double)NPOINTS;

        printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
        printf("Time = %12.8f seconds\n", finish - start);
    }

    return 0
}

int getNumOutside(int nPoints)
{

    struct complex z, c;

    int numOutside = 0;

    double ztemp;

    for (int i = 0; i < nPoints; i++)
    {
        for (int j = 0; j < nPoints; j++)
        {
            c.real = -2.0 + 2.5 * (double)(i) / (double)(nPoints) + 1.0e-7;
            c.imag = 1.125 * (double)(j) / (double)(nPoints) + 1.0e-7;
            z = c;
            for (int iter = 0; iter < MAXITER; iter++)
            {
                ztemp = (z.real * z.real) - (z.imag * z.imag) + c.real;
                z.imag = z.real * z.imag * 2 + c.imag;
                z.real = ztemp;
                if ((z.real * z.real + z.imag * z.imag) > 4.0e0)
                {
                    numoutside++;
                    break;
                }
            }
        }
    }

    return numOutside;
}
