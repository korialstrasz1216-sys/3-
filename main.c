#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matr.h"
#include "Gau.h"

static int init_system(double *A, double *b, int n, int k, const char *filename) {
    if (k == 0) {
        if (read_matrix(filename, A, n) != 0) {
            return 1;
        }
    } else {
        init_matrix_formula(A, n, k);
    }

    build_b(A, n, b);
    return 0;
}

int main(int argc, char **argv) {
    int n, m, k;
    const char *filename;
    double *A, *b, *x;
    int *perm;
    clock_t t0, t1;
    int rc;
    double solve_time, residual, error;

    if (argc != 4 && argc != 5) {
        fprintf(stderr, "Usage: %s n m k [filename]\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    k = atoi(argv[3]);
    filename = NULL;

    if (n <= 0 || m <= 0 || k < 0 || k > 4) {
        fprintf(stderr, "Invalid arguments: n > 0, m > 0, 0 <= k <= 4\n");
        return 1;
    }

    if (k == 0) {
        if (argc != 5) {
            fprintf(stderr, "Error: filename is required when k = 0\n");
            return 1;
        }
        filename = argv[4];
    } else {
        if (argc != 4) {
            fprintf(stderr, "Error: filename must be omitted when k != 0\n");
            return 1;
        }
    }

    A    = (double *)malloc((size_t)n * (size_t)n * sizeof(double));
    b    = (double *)malloc((size_t)n * sizeof(double));
    x    = (double *)malloc((size_t)n * sizeof(double));
    perm = (int *)   malloc((size_t)n * sizeof(int));

    if (!A || !b || !x || !perm) {
        fprintf(stderr, "Memory allocation error\n");
        free(A);
        free(b);
        free(x);
        free(perm);
        return 1;
    }

    if (init_system(A, b, n, k, filename) != 0) {
        free(A);
        free(b);
        free(x);
        free(perm);
        return 1;
    }

    printf("Initial matrix A (no more than %d rows and columns):\n", m);
    print_matrix(A, n, n, m);

    t0 = clock();
    rc = gauss_row_solve(n, A, b, x, perm);
    t1 = clock();

    if (rc != 0) {
        fprintf(stderr, "Error: matrix is singular or zero pivot\n");
        free(A);
        free(b);
        free(x);
        free(perm);
        return 1;
    }

    solve_time = (double)(t1 - t0) / CLOCKS_PER_SEC;

    printf("Solution x (no more than %d elements):\n", m);
    print_matrix(x, 1, n, m);

    printf("Time: %.2f s\n", solve_time);

    /* Restore A and b (Gauss destroyed them) to compute the residual */
    if (init_system(A, b, n, k, filename) != 0) {
        free(A);
        free(b);
        free(x);
        free(perm);
        return 1;
    }

    residual = residual_norm_system(n, A, b, x);
    printf("Residual norm ||Ax-b||/||b|| = %.3e\n", residual);

    error = error_norm_exact(x, n);
    printf("Error norm ||x - x_exact|| = %.3e\n", error);

    free(A);
    free(b);
    free(x);
    free(perm);

    return 0;
}