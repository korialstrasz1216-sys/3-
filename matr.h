#ifndef MATR_H
#define MATR_H

int read_matrix(const char *filename, double *A, int n);
void init_matrix_formula(double *A, int n, int k);
void build_b(const double *A, int n, double *b);
void print_matrix(const double *A, int rows, int cols, int m);
double residual_norm_system(int n, const double *A, const double *b, const double *x);
double error_norm_exact(const double *x, int n);

#endif
