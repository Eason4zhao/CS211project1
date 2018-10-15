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


int main(int argc, char* argv[]) {

        int n = 2048;

        int i, j, k;
        double *a, *b, *c_ijk, *c_ikj, *c_jik, *c_jki, *c_kij, *c_kji;
        double rtime;
        time_t start, end;

        a = calloc(sizeof(double), n*n);
        b = calloc(sizeof(double), n*n);
        c_ijk = calloc(sizeof(double), n*n);
        c_ikj = calloc(sizeof(double), n*n);
        c_jik = calloc(sizeof(double), n*n);
        c_jki = calloc(sizeof(double), n*n);
        c_kij = calloc(sizeof(double), n*n);
        c_kji = calloc(sizeof(double), n*n);

        if(!a || !b || !c_ijk || !c_ikj || !c_jik || !c_jki || !c_kij || !c_kji)
        {
          printf("allocate failed!\n");
          exit(-1);
        }

        // initialization
        for(i = 0; i < n*n; i++)
        {
          a[i] = rand()%1000000/1000.0;
          b[i] = rand()%1000000/1000.0;
          c_ijk[i] = rand()%1000000/1000.0;
          c_ikj[i] = rand()%1000000/1000.0;
          c_jik[i] = rand()%1000000/1000.0;
          c_jki[i] = rand()%1000000/1000.0;
          c_kij[i] = rand()%1000000/1000.0;
          c_kji[i] = rand()%1000000/1000.0;
        }


        //ijk
        start = clock();
        for (i=0; i<n; i++) {
                for (j=0; j<n; j++) {
                        register double r=c_ijk[i*n+j];
                        for (k=0; k<n; k++) {
                                r += a[i*n+k] * b[k*n+j];
                        }
                        c_ijk[i*n+j]=r;
                }
        }
        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of ijk is %f.\n", rtime);

        //ikj
        start = clock();
        for (i=0; i<n; i++) {
                for (k=0; k<n; k++) {
                        register double r = a[i*n+k];
                        for (j=0; j<n; j++)
                                c_ikj[i*n+j] += r * b[k*n+j];
                }
        }

        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of ikj is %f.\n", rtime);

        double err;
        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_ikj[i])>err) {
                        printf("c_ijk[%d]:%f, c_ikj[%d]:%f\n",i, c_ijk[i], i,c_ikj[i]);
                        err = fabs(c_ijk[i]-c_ikj[i]);
                }
        }

        printf("err:%f\n", err);

        //jik
        start = clock();
        for (j=0; j<n; j++) {
                for (i=0; i<n; i++) {
                        register double sum = 0.0;
                        for (k=0; k<n; k++)
                                sum += a[i*n+k] * b[k*n+j];
                        c_jik[i*n+j] = sum;
                }
        }
        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of jik is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_jik[i])>err) {
                        printf("c_ijk[%d]:%f, c_ikj[%d]:%f\n",i, c_ijk[i], i,c_jik[i]);
                        err = fabs(c_ijk[i]-c_jik[i]);
                }
        }

        printf("err:%f\n", err);

        //jki
        start = clock();
        for (j=0; j<n; j++) {
                for (k=0; k<n; k++) {
                        register double r = b[k*n + j];
                        for (i=0; i<n; i++)
                                c_jki[i*n+j] += a[i*n+k] * r;
                }
        }

        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of jki is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_jki[i])>err) {
                        printf("c_ijk[%d]:%f, c_jki[%d]:%f\n",i, c_ijk[i], i,c_jki[i]);
                        err = fabs(c_ijk[i]-c_jki[i]);
                }
        }

        printf("err:%f\n", err);


        //kij
        start = clock();
        for (j=0; j<n; j++) {
                for (i=0; i<n; i++) {
                        register double sum = 0.0;
                        for (k=0; k<n; k++)
                                sum += a[i*n+k] * b[k*n+j];
                        c_kij[i*n+j] = sum;
                }
        }

        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of kij is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_kij[i])>err) {
                        printf("c_ijk[%d]:%f, c_kij[%d]:%f\n",i, c_ijk[i], i,c_kij[i]);
                        err = fabs(c_ijk[i]-c_kij[i]);
                }
        }

        printf("err:%f\n", err);


        //kji

        start = clock();
        for (k=0; k<n; k++) {
                for (j=0; j<n; j++) {
                        register double r = b[k*n+j];
                        for (i=0; i<n; i++)
                                c_kji[i*n+j] += a[i*n+k] * r;
                }
        }

        end = clock();
        rtime = (double)(end-start)/CLOCKS_PER_SEC;
        printf("The running time of kji is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_kji[i])>err) {
                        printf("c_ijk[%d]:%f, c_kji[%d]:%f\n",i, c_ijk[i], i,c_kji[i]);
                        err = fabs(c_ijk[i]-c_kji[i]);
                }
        }
        printf("err:%f\n", err);


}
