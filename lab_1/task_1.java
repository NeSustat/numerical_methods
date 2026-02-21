public class task_1 {
    
    static final double x = 1.0, y = 0.5, z = 2.0;
    static final double dx = 0.005, dy = 0.001, dz = 0.002;
    
    static double func() {
        return Math.log10((x + (2 * y)) / (z + (4 * x)));
    }
    
    static double df_dx() {
        return (1.0 / (x + 2 * y) - 4.0 / (z + 4 * x)) / Math.log(10);
    }
    
    static double df_dy() {
        return 2.0 / ((x + 2 * y) * Math.log(10));
    }
    
    static double df_dz() {
        return -1.0 / ((z + 4 * x) * Math.log(10));
    }
    
    static double absoluteError() {
        return Math.abs(df_dx()) * dx + Math.abs(df_dy()) * dy + Math.abs(df_dz()) * dz;
    }
    
    static double relativeError() {
        return absoluteError() / Math.abs(func());
    }
    
    public static void main(String[] args) {
        System.out.println("Function value: " + func());
        System.out.println("Absolute error: " + absoluteError());
        System.out.println("Relative error: " + relativeError());
    }
}