public class task1 {
    static final double eps = 1e-6, a = 1e-5;

    static double f1(double x1, double x2) { return Math.sqrt(Math.tan(x1 * x2)); }
    static double f2(double x1, double x2) { return Math.sqrt((1 - 0.8 * x1*x1) / 2); }

    static double Nf1(double x1, double x2) { return Math.tan(x1 * x2) - x1*x1; }
    static double Nf2(double x1, double x2) { return 0.8 * x1*x1 + 2 * x2*x2 - 1; }

    static double Nx1(double x1, double x2) { return x1 - (-1.4696) * Nf1(x1,x2) - 0.3914 * Nf2(x1,x2); }
    static double Nx2(double x1, double x2) { return x2 - 0.5879 * Nf1(x1,x2) - 0.3435 * Nf2(x1,x2); }

    static double df1_dx1(double x1, double x2) { return Math.abs(((x2+a) / Math.pow(Math.cos((x1+a)*(x2+a)),2)) / (2 * Math.sqrt(Math.tan((x1-a)*(x2-a))))); }
    static double df1_dx2(double x1, double x2) { return Math.abs(((x1+a) / Math.pow(Math.cos((x1+a)*(x2+a)),2)) / (2 * Math.sqrt(Math.tan((x1-a)*(x2-a))))); }
    static double df2_dx1(double x1)             { return Math.abs(-(2 * Math.sqrt(2) * (x1+a)) / (Math.sqrt(5) * Math.sqrt(5 - 4*(x1+a)*(x1+a)))); }

    public static void main(String[] args) {
        double x = 0.5, y = 0.5, xp = 0.5, yp = 0.5;
        int k = 0;

        System.out.printf("%f = df1_dx1 %f = df1_dx2%n", df1_dx1(x,y), df1_dx2(x,y));
        System.out.printf("%f = df2_dx1 0 = df2_dx2%n", df2_dx1(x));

        if (df1_dx1(x,y) + df2_dx1(x) < 1 && df1_dx2(x,y) < 1) {
            System.out.println("Method simple iteration");
            System.out.println("k|   x1   |  x2  |  delta");
            System.out.printf("%d|   %f   |   %f|    %f%n", k, x, y, Math.max(Math.abs(x-xp), Math.abs(y-yp)));
            do {
                xp = x; yp = y;
                x = f1(xp, yp); y = f2(xp, yp); k++;
                System.out.printf("%d|   %.10f   |   %.10f|    %.10f%n", k, x, y, Math.max(Math.abs(x-xp), Math.abs(y-yp)));
            } while (Math.max(Math.abs(x-xp), Math.abs(y-yp)) > eps);

            System.out.println("\n\nMethod Zeimana");
            k = 0; x = 0.5; y = 0.5; xp = 0.5; yp = 0.5;
            System.out.println("k|   x1   |  x2  |  delta");
            System.out.printf("%d|   %f   |   %f|    %f%n", k, x, y, Math.max(Math.abs(x-xp), Math.abs(y-yp)));
            do {
                xp = x; yp = y;
                x = f1(xp, yp); y = f2(x, yp); k++;
                System.out.printf("%d|   %.10f   |   %.10f|    %.10f%n", k, x, y, Math.max(Math.abs(x-xp), Math.abs(y-yp)));
            } while (Math.max(Math.abs(x-xp), Math.abs(y-yp)) > eps);
        }

        System.out.println("\nN");
        x = 0.5; y = 0.5; k = 0;
        do {
            xp = x; yp = y;
            x = Nx1(xp, yp); y = Nx2(xp, yp); k++;
            System.out.printf("%d|   %.10f   |   %.10f|    %.10f%n", k, x, y, Math.max(Math.abs(x-xp), Math.abs(y-yp)));
        } while (Math.max(Math.abs(x-xp), Math.abs(y-yp)) > eps);
    }
}
