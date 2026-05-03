public class task1 {

    static final int N = 9;
    static double[] X = {0.084, 0.447, 0.810, 1.173, 1.536, 1.898, 2.261, 2.624, 2.987};
    static double[] Y = {-1.732, -1.280, -0.966, -0.634, -0.161, 0.117, 0.555, 0.733, 1.435};

    static double[] gauss3(double[][] A, double[] b) {
        double[][] aug = new double[3][4];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) aug[i][j] = A[i][j];
            aug[i][3] = b[i];
        }
        for (int col = 0; col < 3; col++) {
            int pivot = col;
            for (int row = col+1; row < 3; row++)
                if (Math.abs(aug[row][col]) > Math.abs(aug[pivot][col])) pivot = row;
            double[] tmp = aug[col]; aug[col] = aug[pivot]; aug[pivot] = tmp;
            for (int row = col+1; row < 3; row++) {
                double f = aug[row][col] / aug[col][col];
                for (int k = col; k < 4; k++) aug[row][k] -= f * aug[col][k];
            }
        }
        double[] res = new double[3];
        for (int i = 2; i >= 0; i--) {
            res[i] = aug[i][3];
            for (int j = i+1; j < 3; j++) res[i] -= aug[i][j] * res[j];
            res[i] /= aug[i][i];
        }
        return res;
    }

    // Метод 1: y = ax^2 + bx + c
    static double[] method1() {
        double sx=0, sx2=0, sx3=0, sx4=0, sy=0, sxy=0, sx2y=0;
        for (int i = 0; i < N; i++) {
            sx   += X[i];
            sx2  += X[i]*X[i];
            sx3  += X[i]*X[i]*X[i];
            sx4  += X[i]*X[i]*X[i]*X[i];
            sy   += Y[i];
            sxy  += X[i]*Y[i];
            sx2y += X[i]*X[i]*Y[i];
        }
        double[][] A1 = {{sx4, sx3, sx2},
                         {sx3, sx2, sx },
                         {sx2, sx,  N  }};
        double[] b1 = {sx2y, sxy, sy};
        double[] coef1 = gauss3(A1, b1);
        double a1 = coef1[0], b1c = coef1[1], c1 = coef1[2];

        double nevyazka1 = 0;
        for (int i = 0; i < N; i++) {
            double y_pred1 = a1*X[i]*X[i] + b1c*X[i] + c1;
            nevyazka1 += (Y[i] - y_pred1) * (Y[i] - y_pred1);
        }
        return new double[]{a1, b1c, c1, nevyazka1};
    }

    // Метод 3: y = b*x^a + c  (градиентный спуск)
    static double[] method3() {
        double a3 = 0.5, b3c = 1.0, c3 = -2.0;
        double lr = 0.0001;
        for (int step = 0; step < 50000; step++) {
            double[] err = new double[N];
            for (int i = 0; i < N; i++) err[i] = b3c * Math.pow(X[i], a3) + c3 - Y[i];
            double grad_b = 0, grad_a = 0, grad_c = 0;
            for (int i = 0; i < N; i++) {
                grad_b += err[i] * Math.pow(X[i], a3);
                grad_a += err[i] * b3c * Math.pow(X[i], a3) * Math.log(X[i]);
                grad_c += err[i];
            }
            b3c -= lr * 2 * grad_b;
            a3  -= lr * 2 * grad_a;
            c3  -= lr * 2 * grad_c;
        }
        double nevyazka3 = 0;
        for (int i = 0; i < N; i++) {
            double y_pred3 = b3c * Math.pow(X[i], a3) + c3;
            nevyazka3 += (Y[i] - y_pred3) * (Y[i] - y_pred3);
        }
        return new double[]{a3, b3c, c3, nevyazka3};
    }

    // Метод 6: y = ax + b*e^(-x) + c
    static double[] method6() {
        double[] ex = new double[N];
        for (int i = 0; i < N; i++) ex[i] = Math.exp(-X[i]);

        double sx=0, sy=0, sxx=0, sxex=0, sex2=0, sex=0, sxy6=0, sexy=0;
        for (int i = 0; i < N; i++) {
            sx   += X[i];
            sy   += Y[i];
            sxx  += X[i]*X[i];
            sxex += X[i]*ex[i];
            sex2 += ex[i]*ex[i];
            sex  += ex[i];
            sxy6 += X[i]*Y[i];
            sexy += ex[i]*Y[i];
        }
        double[][] A6 = {{sxx,  sxex, sx },
                         {sxex, sex2, sex},
                         {sx,   sex,  N  }};
        double[] b6 = {sxy6, sexy, sy};
        double[] coef6 = gauss3(A6, b6);
        double a6 = coef6[0], b6c = coef6[1], c6 = coef6[2];

        double nevyazka6 = 0;
        for (int i = 0; i < N; i++) {
            double y_pred6 = a6*X[i] + b6c*ex[i] + c6;
            nevyazka6 += (Y[i] - y_pred6) * (Y[i] - y_pred6);
        }
        return new double[]{a6, b6c, c6, nevyazka6};
    }

    public static void main(String[] args) {
        double[] r1 = method1();
        double[] r3 = method3();
        double[] r6 = method6();

        double a1 = r1[0], b1c = r1[1], c1 = r1[2], nevyazka1 = r1[3];
        double a3 = r3[0], b3c = r3[1], c3 = r3[2], nevyazka3 = r3[3];
        double a6 = r6[0], b6c = r6[1], c6 = r6[2], nevyazka6 = r6[3];

        System.out.println("========================================");
        System.out.println("  Метод наименьших квадратов");
        System.out.println("========================================");
        System.out.println("----------------------------------------");
        System.out.println("  Метод 1: y = ax^2 + bx + c");
        System.out.println("----------------------------------------");
        System.out.printf("  a = %.6f%n", a1);
        System.out.printf("  b = %.6f%n", b1c);
        System.out.printf("  c = %.6f%n", c1);
        System.out.printf("  R = %.6f%n", nevyazka1);
        System.out.println("----------------------------------------");
        System.out.println("  Метод 3: y = b*x^a + c");
        System.out.println("----------------------------------------");
        System.out.printf("  a = %.6f%n", a3);
        System.out.printf("  b = %.6f%n", b3c);
        System.out.printf("  c = %.6f%n", c3);
        System.out.printf("  R = %.6f%n", nevyazka3);
        System.out.println("----------------------------------------");
        System.out.println("  Метод 6: y = ax + b*e^(-x) + c");
        System.out.println("----------------------------------------");
        System.out.printf("  a = %.6f%n", a6);
        System.out.printf("  b = %.6f%n", b6c);
        System.out.printf("  c = %.6f%n", c6);
        System.out.printf("  R = %.6f%n", nevyazka6);
        System.out.println("========================================");

        if (nevyazka1 < nevyazka3 && nevyazka1 < nevyazka6)      System.out.println("  Лучший метод: 1");
        else if (nevyazka3 < nevyazka1 && nevyazka3 < nevyazka6) System.out.println("  Лучший метод: 3");
        else                                                       System.out.println("  Лучший метод: 6");
        System.out.println("========================================");
    }
}
