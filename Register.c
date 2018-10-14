/*
Yinan Zhao
CS211 Project#1
Prof. Chen
Due on 10/15/2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

int main(int argc, char *argv[])
{
  if(argc > 1) {
    int n = atoi(argv[1]);

    int i, j, k;
    double *a, *b, *c, *d, *e, *f;
    double rtime;
    time_t start, end;

    // malloc
    a = (double *) malloc(n*n*sizeof(double));
    b = (double *) malloc(n*n*sizeof(double));
    c = (double *) malloc(n*n*sizeof(double));
    d = (double *) malloc(n*n*sizeof(double));
    e = (double *) malloc(n*n*sizeof(double));
    f = (double *) malloc(n*n*sizeof(double));

    if(!a || !b || !c || !d || !e || !f)
    {
      printf("allocate failed!\n");
      exit(-1);
    }

    // initialization
    for(i = 0; i < n*n; i++)
    {
      a[i] = rand()%1000000/1000.0;
      b[i] = rand()%1000000/1000.0;
      c[i] = rand()%1000000/1000.0;
      d[i] = rand()%1000000/1000.0;
      e[i] = rand()%1000000/1000.0;
      f[i] = rand()%1000000/1000.0;
    }

    // dgemm0: simple ijk version triple loop algorithm
    start = clock();
    for(i = 0; i < n; i++)
	  {
      for(j = 0; j < n; j++)
      {
        for(k = 0; k < n; k++)
        {
          c[i*n+j] += a[i*n+k] * b[k*n+j];
        }
      }
    }

    end = clock();
    rtime = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time for dgemm0 with n= %d is %f s \n", n, rtime);

    // dgemm1: simple ijk version triple loop algorithm with register reuse
    start = clock();

    for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                    register double r = d[i*n+j];
                    for(k = 0; k < n; k++) {
                            r += a[i*n+k] * b[k*n+j];
                    }
                    d[i*n+j] = r;
            }
    }

    end = clock();
    rtime = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Time for dgemm1 with n= %d is %f s \n", n, rtime);


    double error = 0.0;
    for(i=0; i<n*n; i++) {
      if(fabs(c[i]-c[i])>error) {
        printf("c[%d]:%f, c[%d]:%f\n",i, c[i], i,d[i]);
        error = fabs(c[i]-d[i]);
      }
    }

    printf("maximum difference between dgemm0 and dgemm1 is: %f\n", error);

    // dgemm2: more aggresive register reuse
    start = clock();

    for(i = 0; i < n; i += 2) {
            for(j = 0; j < n; j += 2) {
                    for(k = 0; k < n; k += 2) {
                            e[i*n + j] = a[i*n + k] * b[k*n + j] + a[i*n + k+1] * b[(k+1)*n + j] + e[i*n + j];
                            e[(i+1)*n + j] = a[(i+1)*n + k] * b[k*n + j] + a[(i+1)*n + k+1] * b[(k+1)*n + j] + e[(i+1)*n + j];
                            e[i*n + (j+1)] = a[i*n + k] * b[k*n + (j+1)] + a[i*n + k+1] * b[(k+1)*n + (j+1)] + e[i*n + (j+1)];
                            e[(i+1)*n + (j+1)] = a[(i+1)*n + k] * b[k*n + (j+1)] + a[(i+1)*n + k+1] * b[(k+1)*n + (j+1)] + e[(i+1)*n + (j+1)];
                    }
            }

    }

    end = clock();
    rtime = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time for dgemm2 with n= %d is %f s \n", n, rtime);


    // dgemm3
    start = clock();

    for(i = 0; i < n; i += 2) {
            for(j = 0; j < n; j += 2)  {
                    register int t = i*n + j;
                    register int tt = t + n;
                    register double c00 = f[t];
                    register double c01 = f[t+1];
                    register double c10 = f[tt];
                    register double c11 = f[tt+1];

                    for(k = 0; k < n; k += 2) {
                            /* 2 by 2 mini matrix multiplication using registers*/
                            register int ta = i*n + k;
                            register int tta = ta + n;
                            register int tb = k*n + j;
                            register int ttb = tb + n;
                            register double a00 = a[ta];
                            register double a01 = a[ta+1];
                            register double a10 = a[tta];
                            register double a11 = a[tta+1];
                            register double b00 = b[tb];
                            register double b01 = b[tb+1];
                            register double b10 = b[ttb];
                            register double b11 = b[ttb+1];
                            c00 += a00*b00 + a01*b10;
                            c01 += a00*b01 + a01*b11;
                            c10 += a10*b00 + a11*b10;
                            c11 += a10*b01 + a11*b11;
                    }

                    f[t] = c00;
                    f[t+1] = c01;
                    f[tt] = c10;
                    f[tt+1] = c11;
            }

    }

    end = clock();
    rtime = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Time for dgemm3 with n= %d is %f s \n", n, rtime);

    /*double error3 = 0.0;
    for(i=0; i<n*n; i++) {
      if(fabs(e[i]-f[i])>error3) {
        printf("e[%d]:%f, f[%d]:%f\n",i, e[i], i, f[i]);
        error3 = fabs(e[i]-f[i]);
      }
    }
    printf("maximum difference is:%f\n", error3);*/

  }
  else
  {
    printf("Please input the n.\n");
  }
}
