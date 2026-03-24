import math

epsilon = 1e-3
dx = 1e-10

def f(x): return 0.2 * math.exp(-x*x) - math.sqrt(x) + 3
def df(x): return (f(x+dx) - f(x)) / dx
def d2f(x): return (df(x+dx) - df(x)) / dx
def iter_msi(x): return (0.2 * math.exp(-x*x) + 3) ** 2
def iter_newton(x): return x - f(x) / df(x)
def iter_secant(x1, x0): return x1 - f(x1) * (x0 - x1) / (f(x0) - f(x1))

a = 0
while f(a) * f(a+1) > 0:
    a += 1
print(f"[{a};{a+1}]")

print("\nMSI:")
if abs(df(a+1)) < 1:
    k, x2 = 0, (a + a+1) / 2.0
    print("k|x                |delta")
    print(f"{k}|{x2:.25f}|------")
    while True:
        x1 = x2; x2 = iter_msi(x1); k += 1
        print(f"{k}|{x2:.25f}|{abs(x1-x2):.25f}")
        if abs(x1-x2) <= epsilon: break
    print(f"f(x) = {f(x2)}")
else:
    print("It doesn't add up")

print("\nNewton's method")
k, x2 = 0, (a + a+1) / 2.0
print("k|x                |delta")
print(f"{k}|{x2:.15f}|------")
while True:
    x1 = x2; x2 = iter_newton(x1); k += 1
    print(f"{k}|{x2:.15f}|{abs(x1-x2):.15f}")
    if abs(x1-x2) <= epsilon: break
print(f"f(x) = {f(x2)}")

print("\nthe secant method")
k = 0
if df(a) * df(a+1) > 0:
    x2, x1 = (a + a+1) / 2.0, 0.0
    print("k|x                |delta")
    print(f"{k}|{x2:.15f}|------")
    while True:
        buf = x1; x1 = x2; x2 = iter_secant(x1, buf); k += 1
        print(f"{k}|{x2:.15f}|{abs(x1-x2):.15f}")
        if abs(x1-x2) <= epsilon: break
    print(f"f(x) = {f(x2)}")
else:
    print("It doesn't add up")
