# МПИ

k = 0
eps = 1E-3

Xk1 = [0, 0, 0, 0]
Xk2 = [0, 0, 0, 0]

a1 = [[5.554, 0.252, 0.496, 0.237], 
      [0.580, 4.953, 0.467, 0.028], 
      [0.319, 0.372, 8.935, 0.520], 
      [0.043, 0.459, 0.319, 4.778]]

a = [[0 for _ in range(4)] for _ in range(4)]

b1 = [0.442, 0.464, 0.979, 0.126]
b = [0, 0, 0, 0]

edMatrix = [[1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]]

H = [[0.1, 0, 0, 0],
     [0, 0.1, 0, 0],
     [0, 0, 0.1, 0],
     [0, 0, 0, 0.1]]

def calculationsCurX():
    for i in range(4):
        sigma = 0
        for j in range(4):
            sigma += edMatrix[i][j] * Xk1[j]
        Xk2[i] = sigma + b[i]

def rewrite():
    for i in range(4):
        Xk1[i] = Xk2[i]

def checkEnd():
    return max(abs(Xk1[0] - Xk2[0]), abs(Xk1[1] - Xk2[1]), 
               abs(Xk1[2] - Xk2[2]), abs(Xk1[3] - Xk2[3]))

def printCurX(E):
    global k
    print(f"| {k} |", end="")
    for i in range(4):
        print(f"{Xk1[i]:.15f} | ", end="")
    print(f"{E:.4f}")
    k += 1

def checkRes():
    for i in range(4):
        sigma = 0
        for j in range(4):
            sigma += a[i][j] * Xk1[j]
        print(f"\nRes for {i+1} equation: {sigma:.4f} | b_i = {b[i]:.4f} | dif = {abs(sigma - b[i]):.4f}", end="")

if __name__ == "__main__":
    # Вычисляем a = H*A и b = H*b1
    for i in range(4):
        for j in range(4):
            count = 0
            for k_idx in range(4):
                count += a1[i][k_idx] * H[k_idx][j]
            a[i][j] = count
            b[i] += H[i][j] * b1[j]
    
    # edMatrix = E - H*A
    for i in range(4):
        for j in range(4):
            edMatrix[i][j] -= a[i][j]
    
    print("| k |        x1        |         x2        |         x3        |         x4        | delta")
    printCurX(checkEnd())
    calculationsCurX()
    printCurX(checkEnd())
    
    while checkEnd() > eps:
        rewrite()
        calculationsCurX()
        printCurX(checkEnd())
    
    checkRes()
    print("\n\nb: ", end="")
    for val in b:
        print(f"{val} ", end="")
    print()
