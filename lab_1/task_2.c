#include <math.h>
#include <stdio.h>

// Task 1
typedef struct {
    double x0;
    double x;
    double dx;
} Task1;

void task1_init(Task1* t) {
    t->x0 = 81.0;
    t->x = 80.5;
    t->dx = t->x - t->x0;
}

double task1_func(double x) {
    return (sqrt(x) + 1) * (sqrt(x) + 1);
}

double task1_df_dx(double x) {
    return 1 + 1 / sqrt(x);
}

double task1_a(Task1* t) {
    return task1_func(t->x0) + task1_df_dx(t->x0) * t->dx;
}

double task1_absolute_error(Task1* t) {
    return fabs(task1_func(t->x) - task1_a(t));
}

double task1_relative_error(Task1* t) {
    return (task1_absolute_error(t) / task1_func(t->x)) * 100;
}

// Task 2
typedef struct {
    double x0, y0;
    double x, y;
    double dx, dy;
} Task2;

void task2_init(Task2* t) {
    t->x0 = 1.0;
    t->y0 = 1.0;
    t->x = 1.02;
    t->y = 0.97;
    t->dx = t->x - t->x0;
    t->dy = t->y - t->y0;
}

double task2_func(double x, double y) {
    return log(x + y);
}

double task2_df_dx(double x, double y) {
    return 1.0 / (x + y);
}

double task2_df_dy(double x, double y) {
    return 1.0 / (x + y);
}

double task2_a(Task2* t) {
    return task2_func(t->x0, t->y0) + task2_df_dx(t->x0, t->y0) * t->dx + task2_df_dy(t->x0, t->y0) * t->dy;
}

double task2_absolute_error(Task2* t) {
    return fabs(task2_func(t->x, t->y) - task2_a(t));
}

double task2_relative_error(Task2* t) {
    return (task2_absolute_error(t) / task2_func(t->x, t->y)) * 100;
}

int main() {
    Task1 task1;
    task1_init(&task1);
    
    printf("task 1:\n");
    printf("x0 = %f\n", task1.x0);
    printf("x = %f\n", task1.x);
    printf("dx = %f\n", task1.dx);
    printf("A = %.15f\n", task1_func(80.5));
    printf("a = %.15f\n", task1_a(&task1));
    printf("Absolute error: %.6f\n", task1_absolute_error(&task1));
    printf("Relative error: %.6f%%\n\n", task1_relative_error(&task1));
    
    Task2 task2;
    task2_init(&task2);
    
    printf("task 2:\n");
    printf("x0 = %f, y0 = %f\n", task2.x0, task2.y0);
    printf("x = %f, y = %f\n", task2.x, task2.y);
    printf("dx = %f, dy = %f\n", task2.dx, task2.dy);
    printf("A = %.15f\n", task2_func(task2.x, task2.y));
    printf("a = %.15f\n", task2_a(&task2));
    printf("Absolute error: %.6f\n", task2_absolute_error(&task2));
    printf("Relative error: %.6f%%\n", task2_relative_error(&task2));
    
    return 0;
}
