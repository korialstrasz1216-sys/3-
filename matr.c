#include "matr.h"
#include "form.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int read_matrix(const char *filename, double *A, int n) {
    FILE *fp;
    int i, j;

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return 1;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (fscanf(fp, "%lf", &A[i * n + j]) != 1) {
                fprintf(stderr,
                        "Error: invalid data in file %s at element (%d,%d)\n",
                        filename, i + 1, j + 1);
                fclose(fp);
                return 2;
            }
        }
    }

    fclose(fp);
    return 0;
}

void init_matrix_formula(double *A, int n, int k) {
    int i, j;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            A[(i - 1) * n + (j - 1)] = f(k, n, i, j);
        }
    }
}

/* b_i = sum over odd columns (1-based): 1, 3, 5, ... */
void build_b(const double *A, int n, double *b) {
    int i, j;
    double s;

    for (i = 0; i < n; ++i) {
        s = 0.0;
        for (j = 0; j < n; j += 2) {
            s += A[i * n + j];
        }
        b[i] = s;
    }
}

void print_matrix(const double *A, int rows, int cols, int m) {
    int rmax, cmax, i, j;
    rmax = (rows < m) ? rows : m;
    cmax = (cols < m) ? cols : m;

    for (i = 0; i < rmax; ++i) {
        for (j = 0; j < cmax; ++j) {
            printf(" %10.3e", A[i * cols + j]);
        }
        printf("\n");
    }
}

double residual_norm_system(int n, const double *A, const double *b,
                            const double *x) {
    double sum_res2 = 0.0;
    double sum_b2   = 0.0;
    double ax, d, norm_b;
    int i, j;

    for (i = 0; i < n; ++i) {
        ax = 0.0;
        for (j = 0; j < n; ++j) {
            ax += A[i * n + j] * x[j];
        }

        d = ax - b[i];
        sum_res2 += d * d;
        sum_b2   += b[i] * b[i];
    }

    norm_b = sqrt(sum_b2);
    if (norm_b > 0.0) {
        return sqrt(sum_res2) / norm_b;
    }
    return sqrt(sum_res2);
}

double error_norm_exact(const double *x, int n) {
    double sum_err2 = 0.0;
    double exact, d;
    int i;

    for (i = 0; i < n; ++i) {
        /* exact solution is (1, 0, 1, 0, ...) */
        exact = (i % 2 == 0) ? 1.0 : 0.0;
        d = x[i] - exact;
        sum_err2 += d * d;
    }

    return sqrt(sum_err2);
}