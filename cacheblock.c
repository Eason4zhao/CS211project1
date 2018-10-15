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

int main(int argc, char *argv[]) {

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


        int i1, j1, k1;

        int B = 10;

        //ijk
        start = clock();

        for (i = 0; i < n; i+=B) {
                for (j = 0; j < n; j+=B) {
                        for (k = 0; k < n; k+=B) {
                                /* B x B mini matrix multiplications */
                                for (i1 = i; i1 < i+B; i1++) {
                                        for (j1 = j; j1 < j+B; j1++) {
                                                register double r=c_ijk[i1*n+j1];

                                                for (k1 = k; k1 < k+B; k1++) {
                                                        c_ijk[i1*n+j1] += a[i1*n+k1]*b[k1*n+j1];
                                                }
                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of ijk with B = 10 is %f.\n", rtime);

        //ikj

        start = clock();

        for (i = 0; i < n; i+=B) {
                for (k = 0; k < n; k+=B) {
                        for (j = 0; j < n; j+=B) {
                                /* B x B mini matrix multiplications */
                                for (i1 = i; i1 < i+B; i1++) {
                                        for (k1 = k; k1 < k+B; k1++) {
                                                register double r = a[i1*n+k1];
                                                for (j1 = j; j1 < j+B; j1++) {
                                                        c_ikj[i1*n+j1] += r * b[k1*n+j1];
                                                }
                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of ikj with B = 10 is %f.\n", rtime);

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

        for (j = 0; j < n; j+=B) {
                for (i = 0; i < n; i+=B) {
                        for (k = 0; k < n; k+=B) {
                                /* B x B mini matrix multiplications */
                                for (j1 = j; j1 < j+B; j1++) {
                                        for (i1 = i; i1 < i+B; i1++) {
                                                register double r = 0.0;
                                                for (k1 = k; k1 < k+B; k1++) {
                                                        c_jik[i1*n+j1] += a[i1*n+k1] * b[k1*n+j1];
                                                }

                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of jik with B = 10 is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                 if(fabs(c_ijk[i]-c_jik[i])>err) {
                         printf("c_ijk[%d]:%f, c_jik[%d]:%f\n",i, c_ijk[i], i,c_jik[i]);
                         err = fabs(c_ijk[i]-c_jik[i]);
                 }
        }

        printf("err:%f\n", err);


        //jki

        start = clock();

        for (j = 0; j < n; j+=B) {
                for (k = 0; k < n; k+=B) {
                        for (i = 0; i < n; i+=B) {
                                /* B x B mini matrix multiplications */
                                for (j1 = j; j1 < j+B; j1++) {
                                        for (k1 = k; k1 < k+B; k1++) {
                                                register double r = b[k1*n + j1];

                                                for (i1 = i; i1 < i+B; i1++) {
                                                        c_jki[i1*n+j1] += a[i1*n+k1] * r;
                                                }
                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of jki with B = 10 is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_jki[i])>err) {
                        printf("c_ijk[%d]:%f, c_jki[%d]:%f\n",i, c_ijk[i], i,c_jki[i]);
                        err = fabs(c_ijk[i]-c_jki[i]);
                }
        }

        printf("err:%f\n", err);

        //kij

        start = clock();

        for (k = 0; k < n; k+=B) {
                for (i = 0; i < n; i+=B) {
                        for (j = 0; j < n; j+=B) {
                                /* B x B mini matrix multiplications */
                                for (k1 = k; k1 < k+B; k1++) {
                                        for (i1 = i; i1 < i+B; i1++) {
                                                register double r = a[i1*n+k1];

                                                for (j1 = j; j1 < j+B; j1++) {
                                                        c_kij[i1*n+j1] += r * b[k1*n+j1];
                                                }
                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of kij with B = 10 is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_kij[i])>err) {
                        printf("c_ijk[%d]:%f, c_jki[%d]:%f\n",i, c_ijk[i], i,c_kij[i]);
                        err = fabs(c_ijk[i]-c_kij[i]);
                }
        }

        printf("err:%f\n", err);


        //kji
        start = clock();

        for (k = 0; k < n; k+=B) {
                for (j = 0; j < n; j+=B) {
                        for (i = 0; i < n; i+=B) {
                                /* B x B mini matrix multiplications */
                                for (k1 = k; k1 < k+B; k1++) {
                                        for (j1 = j; j1 < j+B; j1++) {
                                                register double r = b[k1*n+j1];

                                                for (i1 = i; i1 < i+B; i1++) {
                                                    c_kji[i1*n+j1] += a[i1*n+k1] * r;

                                                }
                                        }
                                }
                        }
                }
        }
        end = clock();
        rtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The running time of kij with B = 10 is %f.\n", rtime);

        for(i=0,err=0.0; i<n*n; i++) {
                if(fabs(c_ijk[i]-c_kji[i])>err) {
                        printf("c_ijk[%d]:%f, c_jki[%d]:%f\n",i, c_ijk[i], i,c_kji[i]);
                        err = fabs(c_ijk[i]-c_kji[i]);
                }
        }

        printf("err:%f\n", err);



}
