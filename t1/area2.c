#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAXITER 2000

struct complex
{
  double real;
  double imag;
};

int main()
{
  int NPOINTS;
  double area, error, ztemp;
  double start, finish;
  struct complex z, c;

  /*
 *   
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

  for (NPOINTS=1000; NPOINTS <= 1500; NPOINTS += 50)
  {

    int numoutside = 0;
    start = omp_get_wtime();

    for (int i = 0; i < NPOINTS; i++)
    {
      for (int j = 0; j < NPOINTS; j++)
      {
        c.real = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + 1.0e-7;
        c.imag = 1.125 * (double)(j) / (double)(NPOINTS) + 1.0e-7;
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

    finish = omp_get_wtime();

    /*
 *  Calculate area and error and output the results
 */

    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
    error = area / (double)NPOINTS;

    printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
    fprintf(stderr, "%d %12.8f\n", NPOINTS, finish - start);
  }
}