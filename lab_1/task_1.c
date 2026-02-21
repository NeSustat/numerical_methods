#include <math.h>
#include <stdio.h>



const double x = 1.0, y = 0.5, z = 2.0;
const double dx = 0.005, dy = 0.001, dz = 0.002;

double func(){
    return log10((x + (2 * y)) / (z + (4 * x)));
}

double df_dx(){
    return (1.0 / (x + 2 * y) - 4.0 / (z + 4 * x)) / log(10);
}

double df_dy(){
    return 2.0 / ((x + 2 * y) * log(10));
}

double df_dz(){
    return -1.0 / ((z + 4 * x) * log(10));
}

double absoluteError(){
    return fabs(df_dx()) * dx + fabs(df_dy()) * dy + fabs(df_dz()) * dz;
}

double relativeError(){
    return absoluteError() / fabs(func());
}

int main(){
    printf("Function value: %f\n", func());
    printf("Absolute error: %f\n", absoluteError());
    printf("Relative error: %f\n", relativeError());
    return 0;
}