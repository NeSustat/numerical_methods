#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Гаус

double a[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                    {0.580, 4.953, 0.467, 0.028}, 
                    {0.319, 0.372, 8.935, 0.520}, 
                    {0.043, 0.459, 0.319, 4.778}};

double a_copy[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                    {0.580, 4.953, 0.467, 0.028}, 
                    {0.319, 0.372, 8.935, 0.520}, 
                    {0.043, 0.459, 0.319, 4.778}};

double b[4] = {0.442, 0.464, 0.979, 0.126};

double b_copy[4] = {0.442, 0.464, 0.979, 0.126};


double x[4] = {1, 1, 1, 1};

// double a[4][4] = {{1, 2, 3, 4},
//           {3, 0, 1, 2},
//           {1, 1, 1, 1},
//           {2, 3, 4, 5}};

// double b[4] = {1, 2, 3, 4};

void compo(int i){
    for (int string = i + 1; string < 4; string++){
        double k = a[string][i] / a[i][i];
        b[string] = b[string] - b[i] * k;
        for (int j = 0; j < 4; j++){
            a[string][j] = a[string][j] - a[i][j] * k;
        }
    }
}

void resX(){
    for (int i = 3; i >= 0; i--){
        double sum = 0;
        for (int j = 0; j < 4; j++){
            if (j != i) {
                sum += a[i][j] * x[j];
            }
        }
        x[i] = (b[i] - sum) / a[i][i];
    }
}


int main(){
    std::cout << "Gauss\n";
    compo(0);
    compo(1);
    compo(2);
    resX();
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << a[i][j] << " ";
        }
        std::cout << " | " << b[i] << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) std::cout << std::setprecision(10) << "x_" << i+1 << " = " <<  x[i] << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 4; i++){
        std::cout << b_copy[i] << " | " << a_copy[i][0] * x[0] + a_copy[i][1] * x[1] + a_copy[i][2] * x[2] + a_copy[i][3] * x[3] << std::endl;
    }
    std::cout << "\n\nSIM\n";
    system("task3_cpp");
}