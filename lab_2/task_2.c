#include <stdio.h>
#include <math.h>

// Метод Якоби

int k = 0;
const double eps = 1E-3;

double curX[4] = {0, 0, 0, 0};
double lastX[4] = {0, 0, 0, 0};

const double a[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                        {0.580, 4.953, 0.467, 0.028}, 
                        {0.319, 0.372, 8.935, 0.520}, 
                        {0.043, 0.459, 0.319, 4.778}};

const double b[4] = {0.442, 0.464, 0.979, 0.126};

void calculationsCurX(){
    double sigma = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (j != i){
                sigma += a[i][j] * lastX[j];
            }
        }
        curX[i] = (1 / a[i][i]) * (b[i] - sigma);
        sigma = 0;
    }
}

double checkEnd(){
    double max = fabs(curX[0] - lastX[0]);
    for (int i = 1; i < 4; i++){
        double diff = fabs(curX[i] - lastX[i]);
        if (diff > max) max = diff;
    }
    return max;
}

void rewrite(){
    for (int i = 0; i < 4; i++){
        lastX[i] = curX[i];
    }
}

void printCurX(double E){
    printf("| %d |", k);
    for (int i = 0; i < 4; i++){
        printf("%.15f | ", curX[i]);
    }
    printf("%.4f\n", E);
    k++;
}

void checkRes(){
    double sigma = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            sigma += a[i][j] * curX[j];
        }
        printf("\nRes for %d equation: %.4f | b_i = %.4f | dif = %.4f", 
               i+1, sigma, b[i], fabs(sigma - b[i]));
        sigma = 0;
    }
}

int main(){
    printf("| k |        x1        |         x2        |         x3        |         x4        | delta\n");
    printCurX(checkEnd());
    calculationsCurX();
    printCurX(checkEnd());
    
    do {
        rewrite();
        calculationsCurX();
        printCurX(checkEnd());
    } while (checkEnd() > eps);
    
    checkRes();
    printf("\n");
    
    return 0;
}
