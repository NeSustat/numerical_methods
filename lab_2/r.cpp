#include <iostream>
#include <cmath>
#include <iomanip>

const double e = 0.001;

double a[4][4] = {{5.554, 0.252, 0.496, 0.237}, 
                        {0.580, 4.953, 0.467, 0.028}, 
                        {0.319, 0.372, 8.935, 0.520}, 
                        {0.043, 0.459, 0.319, 4.778}};

double b[4] = {0.442, 0.464, 0.979, 0.126};

double x[4] = {0, 0, 0, 0};

void t(){
    for (int i = 0; i < 4; i++ ){
        double aii = a[i][i];
        for (int j = 0; j < 4; j++){
            a[i][j] /= aii;

        }
        b[i] /= aii;
    }
}

int max(){
    int j = 0;
    for (int i = 1; i < 4; i++){
        if (b[i] > b[j]){
            j = i;
        }
    }
    return j;
}

int main(){
    t();
    do {
        int j = max();
        x[j] += b[j];
        for (int i = 0; i < 4; i++){
            if (i != j){
                b[i] -= a[i][j] * b[j];
            }
        }
        b[j] = 0;
    } while (fabs(b[max()]) > e);
    for (auto i : x) std::cout << std::setprecision(15) << i << ' ';
}
// 0.066344211484856  0.076019776456024  0.103303959232729 0.011497517421327
// 0.0660154102823194 0.0833497325898702 0.109569110240627 0.0104544294542382   