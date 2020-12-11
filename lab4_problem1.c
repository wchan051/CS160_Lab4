#include <stdio.h>
#include "omp.h"
#define MAX_THREADS 4
static long num_steps = 1000000;
double step;
int main ()
{
    int i;
    double x = 0.0;
    double pi = 0.0;
    double sum = 0.0;
    double t;
    step = 1.0/(double)num_steps;
    t = omp_get_wtime();
    #pragma omp parallel private(i,x) reduction(+:sum)
    {
        int id = omp_get_thread_num();
        int nth = omp_get_num_threads();
        for(i = id; i < num_steps; i += nth) {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x*x);
        }
    }
    t = omp_get_wtime() - t;
    pi = step * sum;
    printf("pi=%f,time=%f\n",pi,t);
}
