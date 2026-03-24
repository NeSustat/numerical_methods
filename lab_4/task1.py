import math

eps = 1e-6
a = 1e-5

x, y = 0.5, 0.5
x_prev, y_prev = 0.5, 0.5
k = 0

def f1(x1, x2): return math.sqrt(math.tan(x1 * x2))
def f2(x1, x2): return math.sqrt((1 - 0.8 * x1**2) / 2)

def Nf1(x1, x2): return math.tan(x1 * x2) - x1**2
def Nf2(x1, x2): return 0.8 * x1**2 + 2 * x2**2 - 1

def Nx1(x1, x2): return x1 - (-1.4696) * Nf1(x1, x2) - 0.3914 * Nf2(x1, x2)
def Nx2(x1, x2): return x2 - 0.5879 * Nf1(x1, x2) - 0.3435 * Nf2(x1, x2)

def df1_dx1(x1, x2): return abs(((x2+a) / math.cos((x1+a)*(x2+a))**2) / (2 * math.sqrt(math.tan((x1-a)*(x2-a)))))
def df1_dx2(x1, x2): return abs(((x1+a) / math.cos((x1+a)*(x2+a))**2) / (2 * math.sqrt(math.tan((x1-a)*(x2-a)))))
def df2_dx1(x1):     return abs(-(2 * math.sqrt(2) * (x1+a)) / (math.sqrt(5) * math.sqrt(5 - 4*(x1+a)**2)))

print(f"{df1_dx1(x,y)} = df1_dx1 {df1_dx2(x,y)} = df1_dx2")
print(f"{df2_dx1(x)} = df2_dx1 0 = df2_dx2")

if df1_dx1(x,y) + df2_dx1(x) < 1 and df1_dx2(x,y) < 1:
    print("Method simple iteration")
    print("k|   x1   |  x2  |  delta")
    print(f"{k}|   {x}   |   {y}|    {max(abs(x-x_prev), abs(y-y_prev))}")
    while True:
        x_prev, y_prev = x, y
        x, y = f1(x_prev, y_prev), f2(x_prev, y_prev)
        k += 1
        print(f"{k}|   {x:.10f}   |   {y:.10f}|    {max(abs(x-x_prev), abs(y-y_prev)):.10f}")
        if max(abs(x-x_prev), abs(y-y_prev)) <= eps: break

    print("\n\nMethod Zeimana")
    k, x, y, x_prev, y_prev = 0, 0.5, 0.5, 0.5, 0.5
    print("k|   x1   |  x2  |  delta")
    print(f"{k}|   {x}   |   {y}|    {max(abs(x-x_prev), abs(y-y_prev))}")
    while True:
        x_prev, y_prev = x, y
        x = f1(x_prev, y_prev)
        y = f2(x, y_prev)
        k += 1
        print(f"{k}|   {x:.10f}   |   {y:.10f}|    {max(abs(x-x_prev), abs(y-y_prev)):.10f}")
        if max(abs(x-x_prev), abs(y-y_prev)) <= eps: break

print("\nN")
x, y, k = 0.5, 0.5, 0
while True:
    x_prev, y_prev = x, y
    x, y = Nx1(x_prev, y_prev), Nx2(x_prev, y_prev)
    k += 1
    print(f"{k}|   {x:.10f}   |   {y:.10f}|    {max(abs(x-x_prev), abs(y-y_prev)):.10f}")
    if max(abs(x-x_prev), abs(y-y_prev)) <= eps: break
