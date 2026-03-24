public class task1 {
    static final double epsilon = 1e-3, dx = 1e-10;

    static double f(double x) { return 0.2 * Math.exp(-x*x) - Math.sqrt(x) + 3; }
    static double df(double x) { return (f(x+dx) - f(x)) / dx; }
    static double d2f(double x) { return (df(x+dx) - df(x)) / dx; }
    static double iterMSI(double x) { return Math.pow(0.2 * Math.exp(-x*x) + 3, 2); }
    static double iterNewton(double x) { return x - f(x) / df(x); }
    static double iterSecant(double x1, double x0) { return x1 - f(x1) * (x0 - x1) / (f(x0) - f(x1)); }

    public static void main(String[] args) {
        int a = 0;
        while (f(a) * f(a+1) > 0) a++;
        System.out.println("[" + a + ";" + (a+1) + "]");

        System.out.println("\nMSI:");
        int k = 0; double x1 = 0, x2;
        if (Math.abs(df(a+1)) < 1) {
            x2 = (a + a+1) / 2.0;
            System.out.println("k|x                |delta");
            System.out.printf("%d|%.25f|------\n", k, x2);
            do { x1 = x2; x2 = iterMSI(x1); k++;
                System.out.printf("%d|%.25f|%.25f\n", k, x2, Math.abs(x1-x2));
            } while (Math.abs(x1-x2) > epsilon);
            System.out.println("f(x) = " + f(x2));
        } else System.out.println("It doesn't add up");

        System.out.println("\nNewton's method");
        k = 0; x2 = (a + a+1) / 2.0;
        System.out.println("k|x                |delta");
        System.out.printf("%d|%.15f|------\n", k, x2);
        do { x1 = x2; x2 = iterNewton(x1); k++;
            System.out.printf("%d|%.15f|%.15f\n", k, x2, Math.abs(x1-x2));
        } while (Math.abs(x1-x2) > epsilon);
        System.out.println("f(x) = " + f(x2));

        System.out.println("\nthe secant method");
        k = 0;
        if (df(a) * df(a+1) > 0) {
            x2 = (a + a+1) / 2.0; x1 = 0;
            System.out.println("k|x                |delta");
            System.out.printf("%d|%.15f|------\n", k, x2);
            double buf;
            do { buf = x1; x1 = x2; x2 = iterSecant(x1, buf); k++;
                System.out.printf("%d|%.15f|%.15f\n", k, x2, Math.abs(x1-x2));
            } while (Math.abs(x1-x2) > epsilon);
            System.out.println("f(x) = " + f(x2));
        } else System.out.println("It doesn't add up");
    }
}
