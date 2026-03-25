#include <iostream>
#include <cmath>

/*
x | x0 x1 x2 x3
y | y0 y1 y2 y3

y(x) = L(x) = Sigma(l(x)_i)
l(x)i = ((x - x_j)(x - x_j)(x - x_j) / (x_i - x_j)(x_i - x_j)(x_i - x_j)) j≠i

Ньютон
N(x) = y_0 + (y_1 - y_0 / x_1 - x_0)(x - x_0) + (y)
*/

double X[5] = {0.351, 0.867, 1.315, 2.013, 2.859};
double Y[5] = {0.605, 0.218, 0.205, 1.157, 5.092};

double l(int i, double x){
    double a = 1, b = 1;
    for (int j = 0; j < 5; j++){
        if (i != j){
            a *= x - X[j];
            b *= X[i] - X[j];
        }
    }
    return (a * Y[i]) / b;
}

double L(double x){
    double a = 0;
    for (int i = 0; i < 5; i++){
        a += l(i, x);
    }
    return a;
}



int main(){
    std::cout << "Lagransh\nL(x1 + x2) = " << L(X[0] + X[1]) << std::endl;

}