#include <iostream>
#include <cmath>
#include <iomanip>

/*
tan(x1 * x2) - x1 * x1 = 0
0.8(x1 * x1) + 2(x2 * x2) -1 = 0
*/

const double eps = 1E-6;
const double a = .1;

double f1(double x1, double x2){
    return sqrt(tan(x1 * x2)); // = x1
}

double f2(double x1, double x2){
    return sqrt((1 - 0.8 * (x1 * x1)) / 2); // = x2
}

double df1_dx1(double x1, double x2){
    return ((x2 + a) / cos((x1 - a) * (x2 - a)) / cos((x1 - a) * (x2 - a))) / (2 * sqrt(tan((x1 - a) * (x2 - a))));
}

double df1_dx2(double x1, double x2){
    return ((x1 + a) / cos((x1 - a) * (x2 - a)) / cos((x1 - a) * (x2 - a))) / (2 * sqrt(tan((x1 - a) * (x2 - a))));
}

double df2_dx1(double x1){
    return -(2 * sqrt(2) * (x1 + a)) / (sqrt(5) * sqrt(5 - 4 * (x1 + a) * (x1 + a)));
}

int main(){
    
}