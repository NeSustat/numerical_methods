N = 5
X = [0.351, 0.867, 1.315, 2.013, 2.859]
Y = [0.605, 0.218, 0.205, 1.157, 5.092]

def l(i, x):
    a, b = 1, 1
    for j in range(N):
        if i != j:
            a *= x - X[j]
            b *= X[i] - X[j]
    return (a * Y[i]) / b

def L(x):
    return sum(l(i, x) for i in range(N))

def build_newton():
    dd = [[0.0] * N for _ in range(N)]
    for i in range(N):
        dd[i][0] = Y[i]
    for j in range(1, N):
        for i in range(N - j):
            dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (X[i+j] - X[i])
    return dd

def newton(dd, x):
    result = dd[0][0]
    term = 1
    for i in range(1, N):
        term *= x - X[i-1]
        result += dd[0][i] * term
    return result

dd = build_newton()
x = X[0] + X[1]

print("========================================")
print(f"  Interpolation at point x = {x:.6f}")
print("========================================")
print(f"  Lagrange L(x) = {L(x):.6f}")
print(f"  Newton  N(x) = {newton(dd, x):.6f}")
print("========================================")
