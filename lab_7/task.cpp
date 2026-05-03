#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 0.001;
const double A = 1.0, B = 4.0;

double f(double x) {
    return sqrt(x) / (x + 1);
}

double simpson(int n) {
    double h = (B - A) / n;
    double sum = f(A) + f(B);
    for (int i = 1; i < n; i++)
        sum += f(A + i * h) * (i % 2 == 0 ? 2 : 4);
    return sum * h / 3;
}

double trapezoid(int n) {
    double h = (B - A) / n;
    double sum = (f(A) + f(B)) / 2.0;
    for (int i = 1; i < n; i++)
        sum += f(A + i * h);
    return sum * h;
}

void printIteration(int n, double (*method)(int)) {
    double h = (B - A) / n;
    cout << "n = " << n << ", h = " << h << "\n";
    for (int i = 0; i <= n; i++) {
        double xi = A + i * h;
        cout << "  x_" << i << " = " << xi << ",  f(x_" << i << ") = " << f(xi) << "\n";
    }
    cout << "I(n) = " << method(n) << "\n\n";
}

void run(const string& name, double (*method)(int), double divisor) {
    cout << "=== " << name << " ===\n\n";

    struct Row { int n; double I, runge; bool done; };
    vector<Row> table;

    int n = 2;
    double prev = method(n);
    printIteration(n, method);
    table.push_back({n, prev, -1, false});

    while (true) {
        n *= 2;
        double curr = method(n);
        double runge = fabs(curr - prev) / divisor;
        bool done = runge < EPS;

        printIteration(n, method);
        table.push_back({n, curr, runge, done});

        if (done) break;
        prev = curr;
    }

    cout << "Summary table:\n";
    cout << setw(6) << "n" << setw(14) << "I(n)" << setw(14) << "Runge" << setw(8) << "Done" << "\n";
    cout << string(42, '-') << "\n";
    for (auto& r : table) {
        cout << setw(6) << r.n << setw(14) << r.I;
        if (r.runge < 0) cout << setw(14) << "-";
        else             cout << setw(14) << r.runge;
        cout << setw(8) << (r.done ? "yes" : "no") << "\n";
    }
    cout << "\nResult: " << table.back().I << "\n\n";
}

int main() {
    cout << fixed << setprecision(6);
    cout << "f(x) = sqrt(x)/(x+1), a=1, b=4, eps=" << EPS << "\n\n";
    run("Simpson method", simpson, 15.0);
    run("Trapezoid method", trapezoid, 3.0);
    return 0;
}
