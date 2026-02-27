#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

/*
5.554, 0.252, 0.496, 0.237 | 0.442
0.580, 4.953, 0.467, 0.028 | 0.464
0.319, 0.372, 8.935, 0.520 | 0.979
0.043, 0.459, 0.319, 4.778 | 0.126 
*/

int k = 0;
const double eps = 1E-3;

// x_i^(k+1) = 1|a_ii (b_i - SIGMA(x_j^(k)*a_ij))

double curX[4] = {0, 0, 0, 0};

double lastX[4] = {0, 0, 0, 0};

const double a[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                        {0.580, 4.953, 0.467, 0.028}, 
                        {0.319, 0.372, 8.935, 0.520}, 
                        {0.043, 0.459, 0.319, 4.778}};

const double b[4] = {0.442, 0.464, 0.979, 0.126};

void calculationsCurX (){
    double sigma = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (j != i){
                sigma += a[i][j] * lastX[j];
            }
        }
        curX[i] =  (1 / a[i][i]) * (b[i] - sigma);
        sigma = 0;
    }
}

double checkEnd(){
    double a = std::max({(fabs(curX[1] - lastX[1])), (fabs(curX[2] - lastX[2])), (fabs(curX[3] - lastX[3])), (fabs(curX[0] - lastX[0]))});
    return a;
}

void rewrite(){
    for (int i = 0; i < 4; i++){
        lastX[i] = curX[i]; 
    }
}

void printCurX(double E){
    std::cout << "| " << k << " |";
    for (int i = 0; i < 4; i++){
        std::cout << curX[i] << " | ";
    }
    std::cout << std::fixed << std::setprecision(5);
    std::cout << E << "\n";
    std::cout << std::fixed << std::setprecision(15);
    k++;
}

void checkRes(){
    double sigma = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            sigma += a[i][j] * curX[j];
        }
        std::cout << "\nRes for " << i << " equation: " << sigma << " | " << "b_i = " << b[i] << " | dif = " << fabs(sigma - b[i]);
        sigma = 0;
    }
}

int main(){
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "| k |        x1        |         x2        |         x3        |         x4        | delta\n";
    printCurX(checkEnd());
    calculationsCurX();
    printCurX(checkEnd());
    do {
        rewrite(); 
        calculationsCurX();
        printCurX(checkEnd());   
    } while (checkEnd() > eps);
    std::cout << std::fixed << std::setprecision(4);
    checkRes();
}