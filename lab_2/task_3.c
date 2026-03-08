#include <stdio.h>
#include <math.h>

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
    double max = fabs(Xk1[0] - Xk2[0]);
    for (int i = 1; i < 4; i++){
        double diff = fabs(Xk1[i] - Xk2[i]);
        if (diff > max) max = diff;
    }
    return max;
}

void printCurX(double E){
    printf("| %d |", k);
    for (int i = 0; i < 4; i++){
        printf("%.15f | ", Xk1[i]);
    }
    printf("%.4f\n", E);
    k++;
}

void checkRes(){
    for (int i = 0; i < 4; i++){
        double sigma = 0;
        for (int j = 0; j < 4; j++){
            sigma += a[i][j] * Xk1[j];
        }
        printf("\nRes for %d equation: %.4f | b_i = %.4f | dif = %.4f", 
               i+1, sigma, b[i], fabs(sigma - b[i]));
    }
}

int main(){
    // Вычисляем a = H*A и b = H*b1
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            double count = 0;
            for (int k_idx = 0; k_idx < 4; k_idx++){
                count += a1[i][k_idx] * H[k_idx][j];
            }
            a[i][j] = count;
            b[i] += H[i][j] * b1[j];
        }
    }
    
    // edMatrix = E - H*A
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            edMatrix[i][j] -= a[i][j];
        }
    }
    
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
    printf("\n\nb: ");
    for (int i = 0; i < 4; i++){
        printf("%f ", b[i]);
    }
    printf("\n");
    
    return 0;
}
