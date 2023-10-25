#include <omp.h>
#include <cstdio>
#include <cstdlib>

int main() {
    int n;
    FILE *infile = fopen("cube.msh", "r");
    fscanf(infile, "%d%d%d", &n, &n, &n);
    auto ***x = (double ***) malloc(n * sizeof(double ));
    auto ***y = (double ***) malloc(n * sizeof(double ));
    auto ***z = (double ***) malloc(n * sizeof(double ));
    auto ***xn = (double ***) malloc(n * sizeof(double ));
    auto ***yn = (double ***) malloc(n * sizeof(double ));
    auto ***zn = (double ***) malloc(n * sizeof(double ));

    for (int i = 0; i < n; i++) {
        x[i] = (double ) malloc(n * sizeof(double *));
        y[i] = (double ) malloc(n * sizeof(double *));
        z[i] = (double ) malloc(n * sizeof(double *));
        xn[i] = (double ) malloc(n * sizeof(double *));
        yn[i] = (double ) malloc(n * sizeof(double *));
        zn[i] = (double ) malloc(n * sizeof(double *));
        for (int j = 0; j < n; j++) {
            x[i][j] = (double *) malloc(n * sizeof(double));
            y[i][j] = (double *) malloc(n * sizeof(double));
            z[i][j] = (double *) malloc(n * sizeof(double));
            xn[i][j] = (double *) malloc(n * sizeof(double));
            yn[i][j] = (double *) malloc(n * sizeof(double));
            zn[i][j] = (double *) malloc(n * sizeof(double));
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                fscanf(infile, "%le %le %le", &x[i][j][k], &y[i][j][k], &z[i][j][k]);
            }
        }
    }
    fclose(infile);

    int i, j, k;
    static double t1 = omp_get_wtime();
    for (int l = 1; l <= 1000; l++) {
#pragma omp parallel sections private(i, j, k)
        {
#pragma omp section
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    for (k = 0; k < n; k++) {
                        xn[i][j][k] = x[i][j][k] / 2.0;
                        yn[i][j][k] = y[i][j][k] / 2.0;
                        zn[i][j][k] = z[i][j][k] / 2.0;
                    }
                }
            }
        }
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);

    FILE *outfile = fopen("cube_new.msh", "w");
    fprintf(outfile, "%d %d% d\n", n, n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                fprintf(outfile, "%le %le %le\n", xn[i][j][k], yn[i][j][k], zn[i][j][k]);
            }
        }
    }
    fclose(outfile);

    return 0;
}