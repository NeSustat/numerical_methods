import math

class Task1:
    def __init__(self):
        self.x0 = 81
        self.x = 80.5
        self.dx = self.x - self.x0
    
    def func(self, x):
        return (math.sqrt(x) + 1) * (math.sqrt(x) + 1)
    
    def df_dx(self, x):
        return 1 + 1 / math.sqrt(x)
    
    def a(self):
        return self.func(self.x0) + self.df_dx(self.x0) * self.dx
    
    def absolute_error(self):
        return abs(self.func(self.x) - self.a())
    
    def relative_error(self):
        return (self.absolute_error() / self.func(self.x)) * 100


class Task2:
    def __init__(self):
        self.x0 = 1.0
        self.y0 = 1.0
        self.x = 1.02
        self.y = 0.97
        self.dx = self.x - self.x0
        self.dy = self.y - self.y0
    
    def func(self, x, y):
        return math.log(x + y)
    
    def df_dx(self, x, y):
        return 1.0 / (x + y)
    
    def df_dy(self, x, y):
        return 1.0 / (x + y)
    
    def a(self):
        return self.func(self.x0, self.y0) + self.df_dx(self.x0, self.y0) * self.dx + self.df_dy(self.x0, self.y0) * self.dy
    
    def absolute_error(self):
        return abs(self.func(self.x, self.y) - self.a())
    
    def relative_error(self):
        return (self.absolute_error() / self.func(self.x, self.y)) * 100


if __name__ == "__main__":
    task1 = Task1()
    print("task 1:")
    print(f"x0 = {task1.x0}")
    print(f"x = {task1.x}")
    print(f"dx = {task1.dx}")
    print(f"A = {task1.func(80.5):.15f}")
    print(f"a = {task1.a():.15f}")
    print(f"Absolute error: {task1.absolute_error():.6f}")
    print(f"Relative error: {task1.relative_error():.6f}%\n")
    
    task2 = Task2()
    print("task 2:")
    print(f"x0 = {task2.x0}, y0 = {task2.y0}")
    print(f"x = {task2.x}, y = {task2.y}")
    print(f"dx = {task2.dx}, dy = {task2.dy}")
    print(f"A = {task2.func(task2.x, task2.y):.15f}")
    print(f"a = {task2.a():.15f}")
    print(f"Absolute error: {task2.absolute_error():.6f}")
    print(f"Relative error: {task2.relative_error():.6f}%")
