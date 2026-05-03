#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>

const int N = 9;
double X[N] = {0.084, 0.447, 0.810, 1.173, 1.536, 1.898, 2.261, 2.624, 2.987};
double Y[N] = {-1.732, -1.280, -0.966, -0.634, -0.161, 0.117, 0.555, 0.733, 1.435};

std::array<double, 3> gauss3(double A[3][3], double b[3]) {
    double aug[3][4];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) aug[i][j] = A[i][j];
        aug[i][3] = b[i];
    }
    for (int col = 0; col < 3; col++) {
        int pivot = col;
        for (int row = col+1; row < 3; row++)
            if (std::abs(aug[row][col]) > std::abs(aug[pivot][col])) pivot = row;
        for (int k = 0; k < 4; k++) std::swap(aug[col][k], aug[pivot][k]);
        for (int row = col+1; row < 3; row++) {
            double f = aug[row][col] / aug[col][col];
            for (int k = col; k < 4; k++) aug[row][k] -= f * aug[col][k];
        }
    }
    std::array<double, 3> res{};
    for (int i = 2; i >= 0; i--) {
        res[i] = aug[i][3];
        for (int j = i+1; j < 3; j++) res[i] -= aug[i][j] * res[j];
        res[i] /= aug[i][i];
    }
    return res;
}

// Метод 1: y = ax^2 + bx + c
std::array<double, 4> method1() {
    double sx=0, sx2=0, sx3=0, sx4=0, sy=0, sxy=0, sx2y=0;
    for (int i = 0; i < N; i++) {
        sx   += X[i];
        sx2  += X[i]*X[i];
        sx3  += X[i]*X[i]*X[i];
        sx4  += X[i]*X[i]*X[i]*X[i];
        sy   += Y[i];
        sxy  += X[i]*Y[i];
        sx2y += X[i]*X[i]*Y[i];
    }
    double A1[3][3] = {{sx4, sx3, sx2},
                       {sx3, sx2, sx },
                       {sx2, sx,  (double)N}};
    double b1[3] = {sx2y, sxy, sy};
    auto coef1 = gauss3(A1, b1);
    double a1 = coef1[0], b1c = coef1[1], c1 = coef1[2];

    double nevyazka1 = 0;
    for (int i = 0; i < N; i++) {
        double y_pred1 = a1*X[i]*X[i] + b1c*X[i] + c1;
        nevyazka1 += (Y[i] - y_pred1) * (Y[i] - y_pred1);
    }
    return {a1, b1c, c1, nevyazka1};
}

// Метод 3: y = b*x^a + c  (градиентный спуск)
std::array<double, 4> method3() {
    double a3 = 0.5, b3c = 1.0, c3 = -2.0;
    double lr = 0.0001;
    for (int step = 0; step < 50000; step++) {
        double err[N];
        for (int i = 0; i < N; i++) err[i] = b3c * std::pow(X[i], a3) + c3 - Y[i];
        double grad_b = 0, grad_a = 0, grad_c = 0;
        for (int i = 0; i < N; i++) {
            grad_b += err[i] * std::pow(X[i], a3);
            grad_a += err[i] * b3c * std::pow(X[i], a3) * std::log(X[i]);
            grad_c += err[i];
        }
        b3c -= lr * 2 * grad_b;
        a3  -= lr * 2 * grad_a;
        c3  -= lr * 2 * grad_c;
    }
    double nevyazka3 = 0;
    for (int i = 0; i < N; i++) {
        double y_pred3 = b3c * std::pow(X[i], a3) + c3;
        nevyazka3 += (Y[i] - y_pred3) * (Y[i] - y_pred3);
    }
    return {a3, b3c, c3, nevyazka3};
}

// Метод 6: y = ax + b*e^(-x) + c
std::array<double, 4> method6() {
    double ex[N];
    for (int i = 0; i < N; i++) ex[i] = std::exp(-X[i]);

    double sx=0, sy=0, sxx=0, sxex=0, sex2=0, sex=0, sxy6=0, sexy=0;
    for (int i = 0; i < N; i++) {
        sx   += X[i];
        sy   += Y[i];
        sxx  += X[i]*X[i];
        sxex += X[i]*ex[i];
        sex2 += ex[i]*ex[i];
        sex  += ex[i];
        sxy6 += X[i]*Y[i];
        sexy += ex[i]*Y[i];
    }
    double A6[3][3] = {{sxx,  sxex, sx },
                       {sxex, sex2, sex},
                       {sx,   sex,  (double)N}};
    double b6[3] = {sxy6, sexy, sy};
    auto coef6 = gauss3(A6, b6);
    double a6 = coef6[0], b6c = coef6[1], c6 = coef6[2];

    double nevyazka6 = 0;
    for (int i = 0; i < N; i++) {
        double y_pred6 = a6*X[i] + b6c*ex[i] + c6;
        nevyazka6 += (Y[i] - y_pred6) * (Y[i] - y_pred6);
    }
    return {a6, b6c, c6, nevyazka6};
}

int main() {
    auto [a1, b1c, c1, nevyazka1] = method1();
    auto [a3, b3c, c3, nevyazka3] = method3();
    auto [a6, b6c, c6, nevyazka6] = method6();

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "========================================\n";
    std::cout << "  Метод наименьших квадратов\n";
    std::cout << "========================================\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  Метод 1: y = ax^2 + bx + c\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  a = " << a1  << "\n";
    std::cout << "  b = " << b1c << "\n";
    std::cout << "  c = " << c1  << "\n";
    std::cout << "  R = " << nevyazka1 << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  Метод 3: y = b*x^a + c\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  a = " << a3  << "\n";
    std::cout << "  b = " << b3c << "\n";
    std::cout << "  c = " << c3  << "\n";
    std::cout << "  R = " << nevyazka3 << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  Метод 6: y = ax + b*e^(-x) + c\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  a = " << a6  << "\n";
    std::cout << "  b = " << b6c << "\n";
    std::cout << "  c = " << c6  << "\n";
    std::cout << "  R = " << nevyazka6 << "\n";
    std::cout << "========================================\n";

    if (nevyazka1 < nevyazka3 && nevyazka1 < nevyazka6)      std::cout << "  Лучший метод: 1\n";
    else if (nevyazka3 < nevyazka1 && nevyazka3 < nevyazka6) std::cout << "  Лучший метод: 3\n";
    else                                                       std::cout << "  Лучший метод: 6\n";
    std::cout << "========================================\n";

    return 0;
}
