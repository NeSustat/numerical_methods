# Метод Якоби

k = 0
eps = 1E-3

curX = [0, 0, 0, 0]
lastX = [0, 0, 0, 0]

a = [[5.554, 0.252, 0.496, 0.237], 
     [0.580, 4.953, 0.467, 0.028], 
     [0.319, 0.372, 8.935, 0.520], 
     [0.043, 0.459, 0.319, 4.778]]

b = [0.442, 0.464, 0.979, 0.126]

def calculationsCurX():
    for i in range(4):
        sigma = 0
        for j in range(4):
            if j != i:
                sigma += a[i][j] * lastX[j]
        curX[i] = (1 / a[i][i]) * (b[i] - sigma)

def checkEnd():
    return max(abs(curX[0] - lastX[0]), abs(curX[1] - lastX[1]), 
               abs(curX[2] - lastX[2]), abs(curX[3] - lastX[3]))

def rewrite():
    for i in range(4):
        lastX[i] = curX[i]

def printCurX(E):
    global k
    print(f"| {k} |", end="")
    for i in range(4):
        print(f"{curX[i]:.15f} | ", end="")
    print(f"{E:.4f}")
    k += 1

def checkRes():
    for i in range(4):
        sigma = 0
        for j in range(4):
            sigma += a[i][j] * curX[j]
        print(f"\nRes for {i+1} equation: {sigma:.4f} | b_i = {b[i]:.4f} | dif = {abs(sigma - b[i]):.4f}", end="")

if __name__ == "__main__":
    print("| k |        x1        |         x2        |         x3        |         x4        | delta")
    printCurX(checkEnd())
    calculationsCurX()
    printCurX(checkEnd())
    
    while checkEnd() > eps:
        rewrite()
        calculationsCurX()
        printCurX(checkEnd())
    
    checkRes()
    print()
