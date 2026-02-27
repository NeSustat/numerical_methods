import math

x, y, z = 1.0, 0.5, 2.0
dx, dy, dz = 0.005, 0.001, 0.002

def func():
    return math.log10((x + 2 * y) / (z + 4 * x))

def df_dx():
    return (1.0 / (x + 2 * y) - 4.0 / (z + 4 * x)) / math.log(10)

def df_dy():
    return 2.0 / ((x + 2 * y) * math.log(10))

def df_dz():
    return -1.0 / ((z + 4 * x) * math.log(10))

def absoluteError():
    return abs(df_dx()) * dx + abs(df_dy()) * dy + abs(df_dz()) * dz

def relativeError():
    return absoluteError() / abs(func())


print("Function: ", func())
print("Absolute error: ", absoluteError())
print("Relative error: ", relativeError())