#include <stdio.h>
#include <math.h>

#define EPS 0.001
#define A 1.0
#define B 4.0
#define MAX_ROWS 20

double f(double x) {
    return sqrt(x) / (x + 1);
}

double simpson(int n) {
    double h = (B - A) / n, s = f(A) + f(B);
    for (int i = 1; i < n; i++)
        s += f(A + i * h) * (i % 2 == 0 ? 2 : 4);
    return s * h / 3;
}

double trapezoid(int n) {
    double h = (B - A) / n, s = (f(A) + f(B)) / 2.0;
    for (int i = 1; i < n; i++)
        s += f(A + i * h);
    return s * h;
}

void print_iteration(int n, double (*method)(int)) {
    double h = (B - A) / n;
    printf("n = %d, h = %.6f\n", n, h);
    for (int i = 0; i <= n; i++) {
        double xi = A + i * h;
        printf("  x_%d = %.6f,  f(x_%d) = %.6f\n", i, xi, i, f(xi));
    }
    printf("I(n) = %.6f\n\n", method(n));
}

void run(const char* name, double (*method)(int), double divisor) {
    printf("=== %s ===\n\n", name);

    int ns[MAX_ROWS];
    double Is[MAX_ROWS], runges[MAX_ROWS];
    int dones[MAX_ROWS], count = 0;

    int n = 2;
    double prev = method(n);
    print_iteration(n, method);
    ns[count] = n; Is[count] = prev; runges[count] = -1; dones[count] = 0;
    count++;

    while (1) {
        n *= 2;
        double curr = method(n);
        double runge = fabs(curr - prev) / divisor;
        int done = runge < EPS;

        print_iteration(n, method);
        ns[count] = n; Is[count] = curr; runges[count] = runge; dones[count] = done;
        count++;

        if (done) break;
        prev = curr;
    }

    printf("Summary table:\n");
    printf("%6s%14s%14s%8s\n", "n", "I(n)", "Runge", "Done");
    printf("------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (runges[i] < 0)
            printf("%6d%14.6f%14s%8s\n", ns[i], Is[i], "-", dones[i] ? "yes" : "no");
        else
            printf("%6d%14.6f%14.6f%8s\n", ns[i], Is[i], runges[i], dones[i] ? "yes" : "no");
    }
    printf("\nResult: %.6f\n\n", Is[count - 1]);
}

int main() {
    printf("f(x) = sqrt(x)/(x+1), a=1, b=4, eps=%.3f\n\n", EPS);
    run("Simpson method", simpson, 15.0);
    run("Trapezoid method", trapezoid, 3.0);
    return 0;
}
