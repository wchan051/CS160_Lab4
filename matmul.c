#include <stdio.h>
#include <stdlib.h>

#include "omp.h"

#define N 1000

int initialize(double *matrix);
int _initialize(double *matrix);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("pass number of threads as the argument\n");
        return 0;
    }
    int numThreads = atoi(argv[1]);
    int i, j, k;
    double *A, *B, *Cs, *Cp;
    double start, end, timeCost;
    double tsum;

    A = (double *)malloc(sizeof(double) * N * N);
    B = (double *)malloc(sizeof(double) * N * N);
    Cs = (double *)malloc(sizeof(double) * N * N);
    Cp = (double *)malloc(sizeof(double) * N * N);

    initialize(A);
    initialize(B);
    _initialize(Cs);
    _initialize(Cp);

    // sequential version
    start = omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            tsum = 0.0;
            for (k = 0; k < N; k++) tsum += A[i * N + k] * B[k * N + j];
            Cs[i * N + j] = tsum;
        }
    }
    end = omp_get_wtime();
    timeCost = end - start;
    printf("The squential version of matrix multiplication costs %lf seconds\n",
           timeCost);

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    start = omp_get_wtime();
    omp_set_num_threads(numThreads);
    // your parallel version of the above sequential one goes here

    end = omp_get_wtime();
    timeCost = end - start;
    printf(
        "The parallel version of matrix multiplication with %d threads costs "
        "%lf seconds\n",
        numThreads, timeCost);
    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    // verification
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            if (Cs[i * N + j] - Cp[i * N + j] < 0.001 &&
                Cs[i * N + j] - Cp[i * N + j] > -0.001)
                continue;
            else {
                printf("ERRORS DETECTED!!!!!!!!!!!!!\n");
                printf("cs, cp: %f, %f\n", Cs[i*N + j], Cp[i*N+j]);
                return -1;
            }
        }

    // release resources and return
    free(A);
    free(B);
    free(Cs);
    free(Cp);

    return 0;
}

int initialize(double *matrix) {
    srand((unsigned)time(NULL));
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            matrix[i * N + j] = (double)rand() / (double)RAND_MAX;
        }
    printf("Initialized successfully!\n");
    return 0;
}

int _initialize(double *matrix) {
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            matrix[i * N + j] = 0.0;
        }
    printf("Initialized successfully!\n");
    return 0;
}
