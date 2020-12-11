#include <stdio.h>
#include "omp.h"
static long num_steps = 1000000;
double step;
int main ()
{
    int i; 
    double pi = 0.0
    double sum = 0.0;
    double st;
    double rt;
    
    st = omp_get_wtime();
    step = 1.0/(double) num_steps;
    #pragma omp parallel for
    for (i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        #pragma omp atomic
            sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    rt = omp_get_wtime() - st;
    printf("pi=%f,time=%f\n", pi, rt);
}
