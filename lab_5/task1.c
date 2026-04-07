#include <stdio.h>

#define N 5

double X[N] = {0.351, 0.867, 1.315, 2.013, 2.859};
double Y[N] = {0.605, 0.218, 0.205, 1.157, 5.092};
double dd[N][N];

double l(int i, double x) {
    double a = 1, b = 1;
    for (int j = 0; j < N; j++) {
        if (i != j) {
            a *= x - X[j];
            b *= X[i] - X[j];
        }
    }
    return (a * Y[i]) / b;
}

double L(double x) {
    double a = 0;
    for (int i = 0; i < N; i++) a += l(i, x);
    return a;
}

void buildNewton() {
    for (int i = 0; i < N; i++) dd[i][0] = Y[i];
    for (int j = 1; j < N; j++)
        for (int i = 0; i < N - j; i++)
            dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (X[i+j] - X[i]);
}

double Newton(double x) {
    double result = dd[0][0];
    double term = 1;
    for (int i = 1; i < N; i++) {
        term *= x - X[i-1];
        result += dd[0][i] * term;
    }
    return result;
}

int main() {
    buildNewton();
    double x = X[0] + X[1];

    printf("========================================\n");
    printf("  Interpolation at point x = %.6f\n", x);
    printf("========================================\n");
    printf("  Lagrange L(x) = %.6f\n", L(x));
    printf("  Newton  N(x) = %.6f\n", Newton(x));
    printf("========================================\n");
    return 0;
}
