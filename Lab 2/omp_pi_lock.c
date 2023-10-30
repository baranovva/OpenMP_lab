#include <cstdio>
#include <cmath>
#include <omp.h>

#define n 100000000
omp_lock_t lock;

int main() {
    static unsigned int i;
    static double x;
    static double step = 1.0 / (double) n;
    static double sum = 0.0;
    static double thread_sum = 0.0;
    omp_init_lock(&lock);
    static double t1 = omp_get_wtime();
#pragma omp parallel private(x) firstprivate(thread_sum)
    {
#pragma omp for
        for (i = 1; i <= n; i++) {
            x = (i - 0.5) * step;
            thread_sum += 1.0 / sqrt(1.0 - x * x);
        }
        omp_set_lock(&lock);
        sum += thread_sum;
        omp_unset_lock(&lock);
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);
    omp_destroy_lock(&lock);
    printf("Value of the integral: %f\n", step * sum);
    return 0;
}