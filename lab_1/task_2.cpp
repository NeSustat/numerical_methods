#include <cmath>
#include <iostream>
#include <iomanip>

class Task1{
public:
    const double x0 = 81;
    const double x = 80.5;
    const double dx = x - x0;

    double func(double x){
        return (sqrt(x) + 1) * (sqrt(x) + 1);
    }

    double df_dx(double x){
        return 1 + 1/sqrt(x);
    }

    double a(){
        return func(x0) + df_dx(x0) * dx;
    }

    double absoluteError(){
        return fabs(func(x) - a());
    }

    double relativeError(){
        return (absoluteError()/func(x)) * 100;
    }
};

class Task2{
public:
    const double x0 = 1.0;
    const double x = 1.02;
    const double dx = x - x0;
    const double y0 = 1.0;
    const double y = 0.97;
    const double dy = y - y0;

    double func(double x, double y){
        return log(x + y);
    }

    double df_d(double x, double y){
        return 1.0 / (x + y);
    }

    double a(){
        return func(x0, y0) + df_d(x0, y0) * dx + df_d(x0, y0) * dy;
    }

    double absoluteError(){
        return fabs(func(x, y) - a());
    }

    double relativeError(){
        return (absoluteError()/func(x, y)) * 100;
    }
};


int main(){
    Task1 Task1;
    std::cout << "task 1:\n";
    std::cout << "x0 = " << Task1.x0 << std::endl;
    std::cout << "x = " << Task1.x << std::endl;
    std::cout << "dx = " << Task1.dx << std::endl;
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "A = " << Task1.func(80.5) << std::endl;
    std::cout << "a = " << Task1.a() << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Absolute error: " << Task1.absoluteError() << std::endl;
    std::cout << "Relative error: " << Task1.relativeError() << "%\n\n";

    Task2 Task2;
    std::cout << "task 2:\n";
    std::cout << "x0 = " << Task2.x0 << std::endl;
    std::cout << "y0 = " << Task2.y0 << std::endl;
    std::cout << "x = " << Task2.x << std::endl;
    std::cout << "y = " << Task2.y << std::endl;
    std::cout << "dx = " << Task2.dx << std::endl;
    std::cout << "dy = " << Task2.dy << std::endl;
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "A = " << Task2.func(Task2.x, Task2.y) << std::endl;
    std::cout << "a = " << Task2.a() << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Absolute error: " << Task2.absoluteError() << std::endl;
    std::cout << "Relative error: " << Task2.relativeError() << "%\n\n";
}