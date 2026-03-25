#include <iostream>
#include <cmath>
#include <iomanip>

/*
tan(x1 * x2) - x1 * x1 = 0
0.8(x1 * x1) + 2(x2 * x2) -1 = 0
*/

/*
x1^(k+1) = x1^(k) - J[x^(0)]^-1 * f1(x1, x2)
*/

const double eps = 1E-6;
const double a = 1E-5;

double x = .5, y = .5;
double x_prev = .5, y_prev = .5;
int k = 0;

double f1(double x1, double x2){
    return sqrt(tan(x1 * x2)); // = x1
    // return (tan(x1 * x2) / x1);
    // return atan(x1 * x1) / x2;
    // return sqrt((1 - (2 * x2 * x2)) / (.8)); // = x1
}

double f2(double x1, double x2){
    return sqrt((1 - 0.8 * (x1 * x1)) / 2); // = x2
    // return (atan(x1 * x1) / x1);// = x2
}

double Nf1(double x1, double x2){
    return tan(x1 * x2) - x1 * x1;
}

double Nf2(double x1, double x2){
    return 0.8 * (x1 * x1) + 2 * (x2 * x2) -1;
}

double Nx1(double x1, double x2){
    return x1 - (-1.4696) * Nf1(x1, x2) - 0.3914 * Nf2(x1, x2);
}

double Nx2(double x1, double x2){
    return x2 - 0.5879 * Nf1(x1, x2) - 0.3435 * Nf2(x1, x2);
}

double df1_dx1(double x1, double x2){
    return fabs(((x2 + a) / cos((x1 + a) * (x2 + a)) / cos((x1 + a) * (x2 + a))) / (2 * sqrt(tan((x1 - a) * (x2 - a)))));
    // return ((x2 + a) / ((x1 - a) * (pow(cos((x1 - a) * (x2 - a)), 2)))) - (tan((x2 + a) * (x1 + a)) / ((x1 + a) * (x1 + a)));
    // return ((x2 + a) / (pow(x2 + a, 2) * pow(x1 + a, 3) + (x1 + a))) - (atan((x2 + a) * (x1 + a)) / (pow(x1 - a, 2)));
    // return ((10 * (pow((x2 + a), 2))) - 5) / (4 * (pow((x1 - a),2)));
}

double df1_dx2(double x1, double x2){
    return fabs(((x1 + a) / cos((x1 + a) * (x2 + a)) / cos((x1 + a) * (x2 + a))) / (2 * sqrt(tan((x1 - a) * (x2 - a)))));
    // return (1) / (pow(cos((x1 - a) * (x2 - a)),2));
    // return 1 / (pow(x1 - a, 2) * pow(x2 - a, 2) +1);
    // return -((5 * (x2 + a)) / x1);
}

double df2_dx1(double x1){
    return fabs(-(2 * sqrt(2) * (x1 + a)) / (sqrt(5) * sqrt(5 - 4 * (x1 + a) * (x1 + a))));
    // return ((2) / (pow((x1 - a), 4))) - ((atan(pow(x1 + a, 2))) / (pow(x1 - a, 2)));
}

int main(){
    std::cout << df1_dx1(x, y) << " = df1_dx1 " << df1_dx2(x, y) << " = df1_dx2\n";
    std::cout << df2_dx1(x) << " = df2_dx1 0 = df2_dx2\n";
    if (df1_dx1(x, y) + df2_dx1(x) < 1 && df1_dx2(x, y) < 1){
        std::cout << "Method simple iteration\n";
        std::cout << std::setprecision(10);
        std::cout << "k|   x2   |  x2  |  delta \n";
        std::cout << k << "|   " << x << "   |   " << y << "|    " << std::max(fabs(x - x_prev), fabs(y - y_prev)) << "\n";
        do {
            x_prev = x;
            y_prev = y;
            x = f1(x_prev, y_prev);
            y = f2(x_prev, y_prev);
            k++;
            std::cout << k << "|   " << x << "   |   " << y << "|    " << std::max(fabs(x - x_prev), fabs(y - y_prev)) << "\n";

        } while (std::max(fabs(x - x_prev), fabs(y - y_prev)) > eps);

        std::cout << "\n\nMethod Zeimana\n";
        k = 0;
        x = .5, y = .5;
        x_prev = .5, y_prev = .5;
        std::cout << std::setprecision(10);
        std::cout << "k|   x2   |  x2  |  delta \n";
        std::cout << k << "|   " << x << "   |   " << y << "|    " << std::max(fabs(x - x_prev), fabs(y - y_prev)) << "\n";
    
        do {
            x_prev = x;
            y_prev = y;
            x = f1(x_prev, y_prev);
            y = f2(x, y_prev);
            k++;
            std::cout << k << "|   " << x << "   |   " << y << "|    " << std::max(fabs(x - x_prev), fabs(y - y_prev)) << "\n";

        } while (std::max(fabs(x - x_prev), fabs(y - y_prev)) > eps);
    } 
    std::cout << "\nNewtons method\n";
    x = .5, y = .5;
    k = 0;
    if (1){
        do {
            x_prev = x;
            y_prev = y;
            x = Nx1(x_prev, y_prev);
            y = Nx2(x_prev, y_prev);
            k++;
            std::cout << k << "|   " << x << "   |   " << y << "|    " << std::max(fabs(x - x_prev), fabs(y - y_prev)) << "\n";
        } while (std::max(fabs(x - x_prev), fabs(y - y_prev)) > eps);
    }

}