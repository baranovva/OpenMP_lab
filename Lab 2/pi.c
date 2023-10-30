#include <cstdio>
#include <cmath>
#include <omp.h>

#define n 100000000

int main() {
    static double step = 1.0 / (double) n;
    static double sum = 0.0;
    static double x;
    static double t1 = omp_get_wtime();
    for (unsigned long i = 1; i <= n; i++) {
        x = (i - 0.5) * step;
        sum += 1.0 / sqrt(1.0 - x * x);
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    printf("Value of the integral: %f\n", step * sum);
    return 0;
}