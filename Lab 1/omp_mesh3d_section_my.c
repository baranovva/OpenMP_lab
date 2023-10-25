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
    auto ***center_x = (double ***) malloc((n-1) * sizeof(double ));
    auto ***center_y = (double ***) malloc((n-1) * sizeof(double ));
    auto ***center_z = (double ***) malloc((n-1) * sizeof(double ));

    for (int i = 0; i < n; i++) {
        x[i] = (double ) malloc(n * sizeof(double *));
        y[i] = (double ) malloc(n * sizeof(double *));
        z[i] = (double ) malloc(n * sizeof(double *));
        center_x[i] = (double ) malloc((n-1) * sizeof(double *));
        center_y[i] = (double ) malloc((n-1) * sizeof(double *));
        center_z[i] = (double ) malloc((n-1) * sizeof(double *));
        for (int j = 0; j < n; j++) {
            x[i][j] = (double *) malloc(n * sizeof(double));
            y[i][j] = (double *) malloc(n * sizeof(double));
            z[i][j] = (double *) malloc(n * sizeof(double));
            center_x[i][j] = (double *) malloc((n-1) * sizeof(double));
            center_y[i][j] = (double *) malloc((n-1) * sizeof(double));
            center_z[i][j] = (double *) malloc((n-1) * sizeof(double));
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
    for (int l = 1; l <= 100; l++) {
#pragma omp parallel sections private(i, j, k)
        {
#pragma omp section
            for (i = 0; i < n - 1; i++) {
                for (j = 0; j < n - 1; j++) {
                    for (k = 0; k < n - 1; k++) {
                        center_x[i][j][k] = (x[i][j][k] + x[i + 1][j][k]) / 2.0;
                        center_y[i][j][k] = (y[i][j][k] + y[i][j + 1][k]) / 2.0;
                        center_z[i][j][k] = (z[i][j][k] + z[i][j][k + 1]) / 2.0;
                    }
                }
            }
        }
    }
    printf("Computational time = %f\n", omp_get_wtime() - t1);

    FILE *outfile = fopen("cube_new.msh", "w");
    fprintf(outfile, "%d %d% d\n", n-1, n-1, n-1);
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-1; j++) {
            for (k = 0; k < n-1; k++) {
                fprintf(outfile, "%le %le %le\n", center_x[i][j][k], center_y[i][j][k], center_z[i][j][k]);
            }
        }
    }
    fclose(outfile);

    return 0;
}