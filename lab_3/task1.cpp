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

double iterF(double x){
    return pow((0.2 * exp(-x*x) + 3), 2);
}

double df_dx(double x){
    return (f(x+dx) - f(x)) / (dx);
}


int main(){
    while (f(a) * f(a+1) > 0){
        a++;
    }
    std::cout << "[" << a << ";" << a+1 << "]\n";
    if (fabs(df_dx(a+1)) < 1){
        x2 = (a + a+1) / 2.0;
        std::cout << "k|x                |delta\n";
        std::cout << std::fixed << std::setprecision(15);
        std::cout << k << "|"  << x2  << "|------" <<"\n";
        do {
            x1 = x2;
            x2 = iterF(x1);
            k++;
            std::cout << k << "|"  << x2  << "|" << fabs(x1-x2) <<"\n";
        } while (fabs(x1-x2) > epsilon);
        std::cout << df_dx(x2) << "\n";
    } else {
        std::cout << "It doesn't add up\n";
    }
}