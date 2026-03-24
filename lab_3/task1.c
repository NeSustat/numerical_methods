#include <stdio.h>
#include <math.h>

const double epsilon = 1e-3, dx = 1e-10;

double f(double x) { return 0.2 * exp(-x*x) - sqrt(x) + 3; }
double df(double x) { return (f(x+dx) - f(x)) / dx; }
double d2f(double x) { return (df(x+dx) - df(x)) / dx; }
double iter_msi(double x) { return pow(0.2 * exp(-x*x) + 3, 2); }
double iter_newton(double x) { return x - f(x) / df(x); }
double iter_secant(double x1, double x0) { return x1 - f(x1) * (x0 - x1) / (f(x0) - f(x1)); }

int main() {
    int a = 0, k;
    double x1, x2, buf;
    while (f(a) * f(a+1) > 0) a++;
    printf("[%d;%d]\n", a, a+1);

    printf("\nMSI:\n");
    k = 0;
    if (fabs(df(a+1)) < 1) {
        x2 = (a + a+1) / 2.0;
        printf("k|x                |delta\n");
        printf("%d|%.25f|------\n", k, x2);
        do { x1 = x2; x2 = iter_msi(x1); k++;
            printf("%d|%.25f|%.25f\n", k, x2, fabs(x1-x2));
        } while (fabs(x1-x2) > epsilon);
        printf("f(x) = %f\n", f(x2));
    } else printf("It doesn't add up\n");

    printf("\nNewton's method\n");
    k = 0; x2 = (a + a+1) / 2.0;
    printf("k|x                |delta\n");
    printf("%d|%.15f|------\n", k, x2);
    do { x1 = x2; x2 = iter_newton(x1); k++;
        printf("%d|%.15f|%.15f\n", k, x2, fabs(x1-x2));
    } while (fabs(x1-x2) > epsilon);
    printf("f(x) = %f\n", f(x2));

    printf("\nthe secant method\n");
    k = 0;
    if (df(a) * df(a+1) > 0) {
        x2 = (a + a+1) / 2.0; x1 = 0;
        printf("k|x                |delta\n");
        printf("%d|%.15f|------\n", k, x2);
        do { buf = x1; x1 = x2; x2 = iter_secant(x1, buf); k++;
            printf("%d|%.15f|%.15f\n", k, x2, fabs(x1-x2));
        } while (fabs(x1-x2) > epsilon);
        printf("f(x) = %f\n", f(x2));
    } else printf("It doesn't add up\n");
}
