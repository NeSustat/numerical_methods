#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

// МПИ

int k = 0;
const double eps = 1E-3;

double Xk1[4] = {0, 0, 0, 0};

double Xk2[4] = {0, 0, 0, 0};

double a1[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                        {0.580, 4.953, 0.467, 0.028}, 
                        {0.319, 0.372, 8.935, 0.520}, 
                        {0.043, 0.459, 0.319, 4.778}};

double a[4][4];

double b1[4] = {0.442, 0.464, 0.979, 0.126};

double b[4] = {0, 0, 0, 0};

double edMatrix[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};


double H[4][4] = {{0.1, 0, 0, 0},
                {0, 0.1, 0, 0},
                {0, 0, 0.1, 0},
                {0, 0, 0, 0.1}};

// x1^(k+1) = b[0][0] * x1^(k) + b[1][0] * x2^(k) + ... + b[4][0] * x4^(k) + b[0]

void calculationsCurX(){
    for (int i = 0; i < 4; i++){
    double sigma = 0;
        for (int j = 0; j < 4; j++){
            sigma += edMatrix[i][j] * Xk1[j];
        }
        Xk2[i] = sigma + b[i];
    }
}

void rewrite(){
    for (int i = 0; i < 4; i++){
        Xk1[i] = Xk2[i];
    }
}

double checkEnd(){
    return std::max({(fabs(Xk1[1] - Xk2[1])), (fabs(Xk1[2] - Xk2[2])), (fabs(Xk1[3] - Xk2[3])), (fabs(Xk1[0] - Xk2[0]))});
}

void printCurX(double E){
    std::cout << "| " << k << " |";
    for (int i = 0; i < 4; i++){
        std::cout << Xk1[i] << " | ";
    }
    std::cout << std::fixed << std::setprecision(4);
    std::cout << E << "\n";
    std::cout << std::fixed << std::setprecision(15);
    k++;
}

void checkRes(){
    double sigma = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            sigma += a[i][j] * Xk1[j];
        }
        std::cout << "\nRes for " << i+1 << " equation: " << sigma << " | " << "b_i = " << b[i] << " | dif = " << fabs(sigma - b[i]);
        sigma = 0;
    }
}

int main(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            double count = 0;
            for (int k = 0; k < 4; k++){
                count += a1[i][k] * H[k][j];
            }
            a[i][j] = count;
            b[i] += H[i][j] * b1[j];
        }
    }
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j++){
            edMatrix[i][j] -= a[i][j];
        }
    }
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
    std::cout << "\n\nb: ";
    for (double k : b){
        std::cout << k << " ";
    }
}