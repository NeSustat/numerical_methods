public class task1 {
    static final int N = 5;
    static double[] X = {0.351, 0.867, 1.315, 2.013, 2.859};
    static double[] Y = {0.605, 0.218, 0.205, 1.157, 5.092};
    static double[][] dd = new double[N][N];

    static double l(int i, double x) {
        double a = 1, b = 1;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                a *= x - X[j];
                b *= X[i] - X[j];
            }
        }
        return (a * Y[i]) / b;
    }

    static double L(double x) {
        double a = 0;
        for (int i = 0; i < N; i++) a += l(i, x);
        return a;
    }

    static void buildNewton() {
        for (int i = 0; i < N; i++) dd[i][0] = Y[i];
        for (int j = 1; j < N; j++)
            for (int i = 0; i < N - j; i++)
                dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (X[i+j] - X[i]);
    }

    static double Newton(double x) {
        double result = dd[0][0];
        double term = 1;
        for (int i = 1; i < N; i++) {
            term *= x - X[i-1];
            result += dd[0][i] * term;
        }
        return result;
    }

    public static void main(String[] args) {
        buildNewton();
        double x = X[0] + X[1];

        System.out.println("========================================");
        System.out.printf("  Interpolation at point x = %.6f%n", x);
        System.out.println("========================================");
        System.out.printf("  Lagrange L(x) = %.6f%n", L(x));
        System.out.printf("  Newton  N(x) = %.6f%n", Newton(x));
        System.out.println("========================================");
    }
}
