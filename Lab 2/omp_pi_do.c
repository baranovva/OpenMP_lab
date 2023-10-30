#include <cstdio>
#include <cmath>
#include <omp.h>

#define n 100000000

int main() {
    static unsigned int i;
    static double x;
    static double step = 1.0 / (double) n;
    static double sum = 0.0;
    static double t1 = omp_get_wtime();
#pragma omp parallel private(x)
    {
#pragma omp for reduction(+:sum)
        for (i = 1; i <= n; i++) {
            x = (i - 0.5) * step;
            sum += 1.0 / sqrt(1.0 - x * x);
        }
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    printf("Value of the integral: %f\n", step * sum);
    return 0;
}