#include <cstdio>
#include <omp.h>
#include <cmath>

#define SIZE 4
#define n 100000000

int main() {
    static unsigned char tid;
    static unsigned int i;
    static double x, sum[SIZE];
    static double step = 1.0 / (double) n;
    static double t1 = omp_get_wtime();
#pragma omp parallel private(x, tid)
    {
        tid = omp_get_thread_num();
#pragma omp for
        for (i = 1; i <= n; i++) {
            x = (i - 0.5) * step;
            sum[tid] += 1.0 / sqrt(1.0 - x * x);
        }
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    static double pi;
    for (i = 0; i < SIZE; i++) {
        pi += step * sum[i];
    }
    printf("Value of the integral: %f\n", pi);
    return 0;
}
