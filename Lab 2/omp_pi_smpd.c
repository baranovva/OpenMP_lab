#include <cstdio>
#include <omp.h>
#include <cmath>

#define n 100000000

int main() {
    static int i, nthreads, tid, istart, iend;
    static double x;
    static double step = 1.0 / (double) n;
    static double thread_sum = 0.0;
    static double t1 = omp_get_wtime();
#pragma omp parallel private(tid, x, i, istart, iend) reduction(+:thread_sum)
    {
        tid = omp_get_thread_num();
        if (tid == 0) nthreads = omp_get_num_threads();
        istart = tid + 1;
        iend = n;
        for (i = istart; i <= iend; i += nthreads) {
            x = (i - 0.5) * step;
            thread_sum += 1.0 / sqrt(1.0 - x * x);
        }
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    printf("Value of the integral: %f\n", step * thread_sum);
    return 0;
}