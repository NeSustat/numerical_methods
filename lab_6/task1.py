import numpy as np
import matplotlib.pyplot as plt

# исходные данные
x = np.array([0.084, 0.447, 0.810, 1.173, 1.536, 1.898, 2.261, 2.624, 2.987])
y = np.array([-1.732, -1.280, -0.966, -0.634, -0.161, 0.117, 0.555, 0.733, 1.435])
n = len(x)

print("========================================")
print("  Метод наименьших квадратов")
print("========================================")

# =============================================================
# МЕТОД 1: y = ax^2 + bx + c
# =============================================================
# Минимизируем S = Σ(yi - (ax²+bx+c))² -> min
# Приравниваем частные производные к нулю:
#   dS/da = -2 Σ(yi-(axi²+bxi+c))*xi² = 0
#   dS/db = -2 Σ(yi-(axi²+bxi+c))*xi  = 0
#   dS/dc = -2 Σ(yi-(axi²+bxi+c))*1   = 0
# Получаем нормальную систему:
#   a*Σx⁴ + b*Σx³ + c*Σx² = Σx²y
#   a*Σx³ + b*Σx² + c*Σx  = Σxy
#   a*Σx² + b*Σx  + c*n   = Σy

# считаем суммы
sx  = sum(x[i]    for i in range(n))
sx2 = sum(x[i]**2 for i in range(n))
sx3 = sum(x[i]**3 for i in range(n))
sx4 = sum(x[i]**4 for i in range(n))
sy  = sum(y[i]    for i in range(n))
sxy = sum(x[i]*y[i]    for i in range(n))
sx2y= sum(x[i]**2*y[i] for i in range(n))

# составляем и решаем нормальную систему
A1  = [[sx4, sx3, sx2],
       [sx3, sx2, sx ],
       [sx2, sx,  n  ]]
b1  = [sx2y, sxy, sy]

coef1 = np.linalg.solve(A1, b1)
a1, b1c, c1 = coef1

# приближённые значения и невязка
y_pred1 = a1*x**2 + b1c*x + c1

nevyazka1 = 0
for i in range(n):
    nevyazka1 += (y[i] - y_pred1[i])**2

print("----------------------------------------")
print("  Метод 1: y = ax² + bx + c")
print("----------------------------------------")
print(f"  a = {a1:.6f}")
print(f"  b = {b1c:.6f}")
print(f"  c = {c1:.6f}")
print(f"  R = {nevyazka1:.6f}")

# =============================================================
# МЕТОД 3: y = b*x^a + c   (градиентный спуск)
# =============================================================
# Функция нелинейная по параметру a, поэтому нормальную систему
# составить нельзя — используем градиентный спуск.
# S = Σ(yi - (b*xi^a + c))²
# Градиенты:
#   dS/db = 2 * Σ(b*xi^a + c - yi) * xi^a
#   dS/da = 2 * Σ(b*xi^a + c - yi) * b*xi^a*ln(xi)
#   dS/dc = 2 * Σ(b*xi^a + c - yi)

a3, b3c, c3 = 0.5, 1.0, -2.0
lr    = 0.0001
iters = 50000

for step in range(iters):
    err    = [b3c * x[i]**a3 + c3 - y[i] for i in range(n)]
    grad_b = 2 * sum(err[i] * x[i]**a3                    for i in range(n))
    grad_a = 2 * sum(err[i] * b3c * x[i]**a3 * np.log(x[i]) for i in range(n))
    grad_c = 2 * sum(err[i]                                for i in range(n))
    b3c -= lr * grad_b
    a3  -= lr * grad_a
    c3  -= lr * grad_c

y_pred3 = b3c * x**a3 + c3

nevyazka3 = 0
for i in range(n):
    nevyazka3 += (y[i] - y_pred3[i])**2

print("----------------------------------------")
print("  Метод 3: y = b·x^a + c")
print("----------------------------------------")
print(f"  a = {a3:.6f}")
print(f"  b = {b3c:.6f}")
print(f"  c = {c3:.6f}")
print(f"  R = {nevyazka3:.6f}")

# =============================================================
# МЕТОД 6: y = ax + b*e^(-x) + c
# =============================================================
# Базисные функции: phi1=x, phi2=e^(-x), phi3=1
# Нормальная система:
#   a*Σx²     + b*Σx·e⁻ˣ + c*Σx  = Σx·y
#   a*Σx·e⁻ˣ + b*Σe⁻²ˣ  + c*Σe⁻ˣ= Σe⁻ˣ·y
#   a*Σx      + b*Σe⁻ˣ   + c*n   = Σy

ex = np.exp(-x)

sxx  = sum(x[i]**2      for i in range(n))
sxex = sum(x[i]*ex[i]   for i in range(n))
sex2 = sum(ex[i]**2     for i in range(n))
sex  = sum(ex[i]        for i in range(n))
sxy6 = sum(x[i]*y[i]    for i in range(n))
sexy = sum(ex[i]*y[i]   for i in range(n))

A6 = [[sxx,  sxex, sx ],
      [sxex, sex2, sex],
      [sx,   sex,  n  ]]
b6 = [sxy6, sexy, sy]

coef6 = np.linalg.solve(A6, b6)
a6, b6c, c6 = coef6

y_pred6 = a6*x + b6c*ex + c6

nevyazka6 = 0
for i in range(n):
    nevyazka6 += (y[i] - y_pred6[i])**2

print("----------------------------------------")
print("  Метод 6: y = ax + b·e^(-x) + c")
print("----------------------------------------")
print(f"  a = {a6:.6f}")
print(f"  b = {b6c:.6f}")
print(f"  c = {c6:.6f}")
print(f"  R = {nevyazka6:.6f}")
print("========================================")

if nevyazka1 < nevyazka3 and nevyazka1 < nevyazka6:
    print("  Лучший метод: 1")
elif nevyazka3 < nevyazka1 and nevyazka3 < nevyazka6:
    print("  Лучший метод: 3")
else:
    print("  Лучший метод: 6")
print("========================================")

# =============================================================
# графики
# =============================================================
x2    = np.linspace(0.05, 3.05, 300)
y2_m1 = a1*x2**2 + b1c*x2 + c1
y2_m3 = b3c*x2**a3 + c3
y2_m6 = a6*x2 + b6c*np.exp(-x2) + c6

fig, axes = plt.subplots(1, 3, figsize=(15, 5))
fig.suptitle("Метод наименьших квадратов")

axes[0].scatter(x, y, color="black", label="исходные точки", zorder=5)
axes[0].plot(x2, y2_m1, color="blue", label="y = ax² + bx + c")
for i in range(n):
    axes[0].plot([x[i], x[i]], [y[i], y_pred1[i]], color="red", linestyle="--", alpha=0.6)
axes[0].set_title(f"Метод 1\na={a1:.4f}, b={b1c:.4f}, c={c1:.4f}\nR={nevyazka1:.5f}")
axes[0].legend()
axes[0].grid(True)

axes[1].scatter(x, y, color="black", label="исходные точки", zorder=5)
axes[1].plot(x2, y2_m3, color="orange", label="y = b·x^a + c")
for i in range(n):
    axes[1].plot([x[i], x[i]], [y[i], y_pred3[i]], color="red", linestyle="--", alpha=0.6)
axes[1].set_title(f"Метод 3\na={a3:.4f}, b={b3c:.4f}, c={c3:.4f}\nR={nevyazka3:.5f}")
axes[1].legend()
axes[1].grid(True)

axes[2].scatter(x, y, color="black", label="исходные точки", zorder=5)
axes[2].plot(x2, y2_m6, color="green", label="y = ax + b·e^(-x) + c")
for i in range(n):
    axes[2].plot([x[i], x[i]], [y[i], y_pred6[i]], color="red", linestyle="--", alpha=0.6)
axes[2].set_title(f"Метод 6\na={a6:.4f}, b={b6c:.4f}, c={c6:.4f}\nR={nevyazka6:.5f}")
axes[2].legend()
axes[2].grid(True)

plt.tight_layout()
plt.savefig("f:\\vscode_proj\\членоки\\lab_6\\plot.png", dpi=150)
plt.show()