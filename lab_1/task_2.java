public class task_2 {
    
    static class Task1 {
        double x0 = 81.0;
        double x = 80.5;
        double dx = x - x0;
        
        double func(double x) {
            return (Math.sqrt(x) + 1) * (Math.sqrt(x) + 1);
        }
        
        double df_dx(double x) {
            return 1 + 1 / Math.sqrt(x);
        }
        
        double a() {
            return func(x0) + df_dx(x0) * dx;
        }
        
        double absoluteError() {
            return Math.abs(func(x) - a());
        }
        
        double relativeError() {
            return (absoluteError() / func(x)) * 100;
        }
    }
    
    static class Task2 {
        double x0 = 1.0, y0 = 1.0;
        double x = 1.02, y = 0.97;
        double dx = x - x0, dy = y - y0;
        
        double func(double x, double y) {
            return Math.log(x + y);
        }
        
        double df_dx(double x, double y) {
            return 1.0 / (x + y);
        }
        
        double df_dy(double x, double y) {
            return 1.0 / (x + y);
        }
        
        double a() {
            return func(x0, y0) + df_dx(x0, y0) * dx + df_dy(x0, y0) * dy;
        }
        
        double absoluteError() {
            return Math.abs(func(x, y) - a());
        }
        
        double relativeError() {
            return (absoluteError() / func(x, y)) * 100;
        }
    }
    
    public static void main(String[] args) {
        Task1 task1 = new Task1();
        System.out.println("task 1:");
        System.out.println("x0 = " + task1.x0);
        System.out.println("x = " + task1.x);
        System.out.println("dx = " + task1.dx);
        System.out.printf("A = %.15f%n", task1.func(80.5));
        System.out.printf("a = %.15f%n", task1.a());
        System.out.printf("Absolute error: %.6f%n", task1.absoluteError());
        System.out.printf("Relative error: %.6f%%%n%n", task1.relativeError());
        
        Task2 task2 = new Task2();
        System.out.println("task 2:");
        System.out.println("x0 = " + task2.x0 + ", y0 = " + task2.y0);
        System.out.println("x = " + task2.x + ", y = " + task2.y);
        System.out.println("dx = " + task2.dx + ", dy = " + task2.dy);
        System.out.printf("A = %.15f%n", task2.func(task2.x, task2.y));
        System.out.printf("a = %.15f%n", task2.a());
        System.out.printf("Absolute error: %.6f%n", task2.absoluteError());
        System.out.printf("Relative error: %.6f%%%n", task2.relativeError());
    }
}
