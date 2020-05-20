#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 

# define MAXITER 2000

struct complex{
  double real;
  double imag;
};

int main(){
  int NPOINTS;



for(NPOINTS=500; NPOINTS<=5000; NPOINTS+=500) {


  int numoutside = 0;
  int i;
  int j;
  int iter;
  double area, error, ztemp;
  double start, finish;
  struct complex z, c;

  start = omp_get_wtime();

  #pragma omp parallel private (i,j,iter,c,z,ztemp) reduction(+:numoutside)
  {

    #pragma omp for
          for (i=0; i<NPOINTS; i++) {
                for (j=0; j<NPOINTS; j++) {

                  c.real = -2.0+2.5(double)(i)/(double)(NPOINTS)+1.0e-7;
                  c.imag = 1.125(double)(j)/(double)(NPOINTS)+1.0e-7;
                  z=c;

                  for (iter=0; iter<MAXITER; iter++){

                        ztemp=(z.realz.real)-(z.imagz.imag)+c.real;
                        z.imag=z.realz.imag2+c.imag; 
                        z.real=ztemp; 

                        if ((z.realz.real+z.imagz.imag)>4.0e0) {
                          numoutside++; 
                          break;
                        }
                  }
                }
          }
        }


  finish = omp_get_wtime();


      area = 2.02.51.125(double)(NPOINTSNPOINTS-numoutside)/(double)(NPOINTS*$
      error = area/(double)NPOINTS;

      printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
      fprintf(stderr,"%d %12.8f\n",NPOINTS,finish-start);
   }
 }
