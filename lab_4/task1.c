#include <stdio.h>
#include <math.h>

const double eps = 1e-6, a = 1e-5;

double f1(double x1, double x2) { return sqrt(tan(x1 * x2)); }
double f2(double x1, double x2) { return sqrt((1 - 0.8 * x1*x1) / 2); }

double Nf1(double x1, double x2) { return tan(x1 * x2) - x1*x1; }
double Nf2(double x1, double x2) { return 0.8 * x1*x1 + 2 * x2*x2 - 1; }

double Nx1(double x1, double x2) { return x1 - (-1.4696) * Nf1(x1,x2) - 0.3914 * Nf2(x1,x2); }
double Nx2(double x1, double x2) { return x2 - 0.5879 * Nf1(x1,x2) - 0.3435 * Nf2(x1,x2); }

double df1_dx1(double x1, double x2) { return fabs(((x2+a) / pow(cos((x1+a)*(x2+a)),2)) / (2 * sqrt(tan((x1-a)*(x2-a))))); }
double df1_dx2(double x1, double x2) { return fabs(((x1+a) / pow(cos((x1+a)*(x2+a)),2)) / (2 * sqrt(tan((x1-a)*(x2-a))))); }
double df2_dx1(double x1)             { return fabs(-(2 * sqrt(2) * (x1+a)) / (sqrt(5) * sqrt(5 - 4*(x1+a)*(x1+a)))); }

int main() {
    double x = 0.5, y = 0.5, xp = 0.5, yp = 0.5;
    int k = 0;

    printf("%f = df1_dx1 %f = df1_dx2\n", df1_dx1(x,y), df1_dx2(x,y));
    printf("%f = df2_dx1 0 = df2_dx2\n", df2_dx1(x));

    if (df1_dx1(x,y) + df2_dx1(x) < 1 && df1_dx2(x,y) < 1) {
        printf("Method simple iteration\n");
        printf("k|   x1   |  x2  |  delta\n");
        printf("%d|   %f   |   %f|    %f\n", k, x, y, fmax(fabs(x-xp), fabs(y-yp)));
        do {
            xp = x; yp = y;
            x = f1(xp, yp); y = f2(xp, yp); k++;
            printf("%d|   %.10f   |   %.10f|    %.10f\n", k, x, y, fmax(fabs(x-xp), fabs(y-yp)));
        } while (fmax(fabs(x-xp), fabs(y-yp)) > eps);

        printf("\n\nMethod Zeimana\n");
        k = 0; x = 0.5; y = 0.5; xp = 0.5; yp = 0.5;
        printf("k|   x1   |  x2  |  delta\n");
        printf("%d|   %f   |   %f|    %f\n", k, x, y, fmax(fabs(x-xp), fabs(y-yp)));
        do {
            xp = x; yp = y;
            x = f1(xp, yp); y = f2(x, yp); k++;
            printf("%d|   %.10f   |   %.10f|    %.10f\n", k, x, y, fmax(fabs(x-xp), fabs(y-yp)));
        } while (fmax(fabs(x-xp), fabs(y-yp)) > eps);
    }

    printf("\nN\n");
    x = 0.5; y = 0.5; k = 0;
    do {
        xp = x; yp = y;
        x = Nx1(xp, yp); y = Nx2(xp, yp); k++;
        printf("%d|   %.10f   |   %.10f|    %.10f\n", k, x, y, fmax(fabs(x-xp), fabs(y-yp)));
    } while (fmax(fabs(x-xp), fabs(y-yp)) > eps);
}
