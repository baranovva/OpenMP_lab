#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define n 100000000

int main() {
    auto *x = (double *) malloc(sizeof(double) * n);
    auto *y = (double *) malloc(sizeof(double) * n);
    for (static unsigned long i = 0; i < n; i++) {
        x[i] = 1.0;
        y[i] = 2.0;
    }
    static double s = 0.1;
    static double t1 = omp_get_wtime();
    for (static unsigned long i = 0; i < n; i++) {
        y[i] += s * x[i];
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    printf("Values of vector elements: %f\n", y[0]);
    return 0;
}