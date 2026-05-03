import math

EPS = 0.001
A, B = 1.0, 4.0

def f(x):
    return math.sqrt(x) / (x + 1)

def simpson(n):
    h = (B - A) / n
    s = f(A) + f(B)
    for i in range(1, n):
        s += f(A + i * h) * (2 if i % 2 == 0 else 4)
    return s * h / 3

def trapezoid(n):
    h = (B - A) / n
    s = (f(A) + f(B)) / 2
    for i in range(1, n):
        s += f(A + i * h)
    return s * h

def print_iteration(n, method):
    h = (B - A) / n
    print(f"n = {n}, h = {h:.6f}")
    for i in range(n + 1):
        xi = A + i * h
        print(f"  x_{i} = {xi:.6f},  f(x_{i}) = {f(xi):.6f}")
    print(f"I(n) = {method(n):.6f}\n")

def run(name, method, divisor):
    print(f"=== {name} ===\n")
    table = []

    n = 2
    prev = method(n)
    print_iteration(n, method)
    table.append((n, prev, None, False))

    while True:
        n *= 2
        curr = method(n)
        runge = abs(curr - prev) / divisor
        done = runge < EPS

        print_iteration(n, method)
        table.append((n, curr, runge, done))

        if done:
            break
        prev = curr

    print("Summary table:")
    print(f"{'n':>6}{'I(n)':>14}{'Runge':>14}{'Done':>8}")
    print("-" * 42)
    for row in table:
        runge_str = "-" if row[2] is None else f"{row[2]:.6f}"
        print(f"{row[0]:>6}{row[1]:>14.6f}{runge_str:>14}{'yes' if row[3] else 'no':>8}")
    print(f"\nResult: {table[-1][1]:.6f}\n")

print(f"f(x) = sqrt(x)/(x+1), a=1, b=4, eps={EPS}\n")
run("Simpson method", simpson, 15.0)
run("Trapezoid method", trapezoid, 3.0)
