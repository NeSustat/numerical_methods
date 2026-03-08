# Гаус

a = [[5.554, 0.252, 0.496, 0.237], 
     [0.580, 4.953, 0.467, 0.028], 
     [0.319, 0.372, 8.935, 0.520], 
     [0.043, 0.459, 0.319, 4.778]]

a_copy = [[5.554, 0.252, 0.496, 0.237], 
          [0.580, 4.953, 0.467, 0.028], 
          [0.319, 0.372, 8.935, 0.520], 
          [0.043, 0.459, 0.319, 4.778]]

b = [0.442, 0.464, 0.979, 0.126]

b_copy = [0.442, 0.464, 0.979, 0.126]

x = [1, 1, 1, 1]

def compo(i):
    for string in range(i + 1, 4):
        k = a[string][i] / a[i][i]
        b[string] = b[string] - b[i] * k
        for j in range(4):
            a[string][j] = a[string][j] - a[i][j] * k

def resX():
    for i in range(3, -1, -1):
        sum_val = 0
        for j in range(4):
            if j != i:
                sum_val += a[i][j] * x[j]
        x[i] = (b[i] - sum_val) / a[i][i]

if __name__ == "__main__":
    compo(0)
    compo(1)
    compo(2)
    resX()
    
    for i in range(4):
        for j in range(4):
            print(a[i][j], end=" ")
        print(f" | {b[i]}")
    
    print()
    for i in range(4):
        print(f"{x[i]:.10f}")
    
    print()
    for i in range(4):
        result = a_copy[i][0] * x[0] + a_copy[i][1] * x[1] + a_copy[i][2] * x[2] + a_copy[i][3] * x[3]
        print(f"{b_copy[i]} | {result}")
