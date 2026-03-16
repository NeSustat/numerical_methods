#include <iostream>
#include <cmath>
#include <iomanip>

// f(x) = 0.2 exp(-x^2) - sqrt(x) + 3

const double epsilon = 1E-3;
const double dx = 1E-10;

int a = 0;
int k = 0;
double x1 = 0;
double x2 = 0;

double f(double x){
    return 0.2 * exp(-x*x) - sqrt(x) + 3;
}

double df_dx(double x){
    return (f(x+dx) - f(x)) / (dx);
}

double d2f_dx2(double x){
    return (df_dx(x+dx) - df_dx(x)) / (dx);
}

double iterF_MSI(double x){
    return pow((0.2 * exp(-x*x) + 3), 2);
}

double iter_Newton(double x){
    return x - (f(x) / df_dx(x));
}

double iter_Secants(double x_1, double x_0){
    return (x_1 - (f(x_1) * (x_0 - x_1)) / (f(x_0)-f(x_1)));
}


int main(){
    while (f(a) * f(a+1) > 0){
        a++;
    }
    std::cout << "[" << a << ";" << a+1 << "]\n";
    std::cout << "\nMSI:\n";
    if (fabs(df_dx(a+1)) < 1){
        x2 = (a + a+1) / 2.0;
        std::cout << "k|x                |delta\n";
        std::cout << std::fixed << std::setprecision(15);
        std::cout << k << "|"  << x2  << "|------" <<"\n";
        do {
            x1 = x2;
            x2 = iterF_MSI(x1);
            k++;
            std::cout << k << "|"  << x2  << "|" << fabs(x1-x2) <<"\n";
        } while (fabs(x1-x2) > epsilon);
        std::cout << "f(x) = " << f(x2) << "\n";
    } else {
        std::cout << "It doesn't add up\n";
    }

    std::cout << "\nNewton's method\n";
    k = 0;
    x2 = (a + a+1) / 2.0;
    if (f(x2) * d2f_dx2(x2) > 0 || 1){
        std::cout << "k|x                |delta\n";
        std::cout << std::fixed << std::setprecision(15);
        std::cout << k << "|"  << x2  << "|------" <<"\n";
        do {
            x1 = x2;
            x2 = iter_Newton(x1);
            k++;
            std::cout << k << "|"  << x2  << "|" << fabs(x1-x2) <<"\n";
        } while (fabs(x1-x2) > epsilon);
        std::cout << "f(x) = " << f(x2) << "\n";
    } else {
        std::cout << "It doesn't add up\n";
    }

    std::cout << "\nthe secant method\n";
    k = 0;
    if (df_dx(a) * df_dx(a+1) > 0){
        x2 = (a + a+1) / 2.0;
        x1 = 0;
        int buffer = 0;
        std::cout << "k|x                |delta\n";
        std::cout << std::fixed << std::setprecision(15);
        std::cout << k << "|"  << x2  << "|------" <<"\n";
        do {
            buffer = x1;
            x1 = x2;
            x2 = iter_Secants(x1, buffer);
            k++;
            std::cout << k << "|"  << x2  << "|" << fabs(x1-x2) <<"\n";
        } while (fabs(x1-x2) > epsilon);
        std::cout << "f(x) = " << f(x2) << "\n";
    } else {
        std::cout << "It doesn't add up\n";
    }
}