import java.util.ArrayList;
import java.util.List;

public class task {
    static final double EPS = 0.001;
    static final double A = 1.0, B = 4.0;

    static double f(double x) {
        return Math.sqrt(x) / (x + 1);
    }

    static double simpson(int n) {
        double h = (B - A) / n, s = f(A) + f(B);
        for (int i = 1; i < n; i++)
            s += f(A + i * h) * (i % 2 == 0 ? 2 : 4);
        return s * h / 3;
    }

    static double trapezoid(int n) {
        double h = (B - A) / n, s = (f(A) + f(B)) / 2.0;
        for (int i = 1; i < n; i++)
            s += f(A + i * h);
        return s * h;
    }

    static void printIteration(int n, boolean isSimpson) {
        double h = (B - A) / n;
        System.out.printf("n = %d, h = %.6f%n", n, h);
        for (int i = 0; i <= n; i++) {
            double xi = A + i * h;
            System.out.printf("  x_%d = %.6f,  f(x_%d) = %.6f%n", i, xi, i, f(xi));
        }
        double I = isSimpson ? simpson(n) : trapezoid(n);
        System.out.printf("I(n) = %.6f%n%n", I);
    }

    static void run(String name, boolean isSimpson, double divisor) {
        System.out.printf("=== %s ===%n%n", name);

        record Row(int n, double I, double runge, boolean done) {}
        List<Row> table = new ArrayList<>();

        int n = 2;
        double prev = isSimpson ? simpson(n) : trapezoid(n);
        printIteration(n, isSimpson);
        table.add(new Row(n, prev, -1, false));

        while (true) {
            n *= 2;
            double curr = isSimpson ? simpson(n) : trapezoid(n);
            double runge = Math.abs(curr - prev) / divisor;
            boolean done = runge < EPS;

            printIteration(n, isSimpson);
            table.add(new Row(n, curr, runge, done));

            if (done) break;
            prev = curr;
        }

        System.out.println("Summary table:");
        System.out.printf("%6s%14s%14s%8s%n", "n", "I(n)", "Runge", "Done");
        System.out.println("-".repeat(42));
        for (Row r : table) {
            String ruStr = r.runge() < 0 ? "-" : String.format("%.6f", r.runge());
            System.out.printf("%6d%14.6f%14s%8s%n", r.n(), r.I(), ruStr, r.done() ? "yes" : "no");
        }
        System.out.printf("%nResult: %.6f%n%n", table.getLast().I());
    }

    public static void main(String[] args) {
        System.out.printf("f(x) = sqrt(x)/(x+1), a=1, b=4, eps=%.3f%n%n", EPS);
        run("Simpson method", true, 15.0);
        run("Trapezoid method", false, 3.0);
    }
}
