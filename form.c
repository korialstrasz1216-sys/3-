#include "form.h"
#include <math.h>

double f(int k, int n, int i, int j) {
    double ii = (double)i;
    double jj = (double)j;

    switch (k) {
        case 1:
            return (double)n - (double)(i > j ? i : j) + 1.0;
        case 2:
            return (double)(i > j ? i : j);
        case 3:
            return fabs(ii - jj);
        case 4:
            return 1.0 / (ii + jj - 1.0);
        default:
            return 0.0;
    }
}