import java.util.Arrays;

// МПИ

public class task_3 {
    static int k = 0;
    static final double eps = 1E-3;

    static double[] Xk1 = {0, 0, 0, 0};
    static double[] Xk2 = {0, 0, 0, 0};

    static final double[][] a1 = {{5.554, 0.252, 0.496, 0.237}, 
                                  {0.580, 4.953, 0.467, 0.028}, 
                                  {0.319, 0.372, 8.935, 0.520}, 
                                  {0.043, 0.459, 0.319, 4.778}};

    static double[][] a = new double[4][4];

    static final double[] b1 = {0.442, 0.464, 0.979, 0.126};
    static double[] b = {0, 0, 0, 0};

    static double[][] edMatrix = {{1, 0, 0, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 1, 0},
                                  {0, 0, 0, 1}};

    static final double[][] H = {{0.1, 0, 0, 0},
                                 {0, 0.1, 0, 0},
                                 {0, 0, 0.1, 0},
                                 {0, 0, 0, 0.1}};

    static void calculationsCurX(){
        for (int i = 0; i < 4; i++){
            double sigma = 0;
            for (int j = 0; j < 4; j++){
                sigma += edMatrix[i][j] * Xk1[j];
            }
            Xk2[i] = sigma + b[i];
        }
    }

    static void rewrite(){
        for (int i = 0; i < 4; i++){
            Xk1[i] = Xk2[i];
        }
    }

    static double checkEnd(){
        return Arrays.stream(new double[]{
            Math.abs(Xk1[0] - Xk2[0]), 
            Math.abs(Xk1[1] - Xk2[1]),
            Math.abs(Xk1[2] - Xk2[2]), 
            Math.abs(Xk1[3] - Xk2[3])
        }).max().getAsDouble();
    }

    static void printCurX(double E){
        System.out.print("| " + k + " |");
        for (int i = 0; i < 4; i++){
            System.out.printf("%.15f | ", Xk1[i]);
        }
        System.out.printf("%.4f%n", E);
        k++;
    }

    static void checkRes(){
        for (int i = 0; i < 4; i++){
            double sigma = 0;
            for (int j = 0; j < 4; j++){
                sigma += a[i][j] * Xk1[j];
            }
            System.out.printf("%nRes for %d equation: %.4f | b_i = %.4f | dif = %.4f", 
                            i+1, sigma, b[i], Math.abs(sigma - b[i]));
        }
    }

    public static void main(String[] args){
        // Вычисляем a = H*A и b = H*b1
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                double count = 0;
                for (int k_idx = 0; k_idx < 4; k_idx++){
                    count += a1[i][k_idx] * H[k_idx][j];
                }
                a[i][j] = count;
                b[i] += H[i][j] * b1[j];
            }
        }
        
        // edMatrix = E - H*A
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                edMatrix[i][j] -= a[i][j];
            }
        }
        
        System.out.println("| k |        x1        |         x2        |         x3        |         x4        | delta");
        printCurX(checkEnd());
        calculationsCurX();
        printCurX(checkEnd());
        
        do {
            rewrite();
            calculationsCurX();
            printCurX(checkEnd());
        } while (checkEnd() > eps);
        
        checkRes();
        System.out.print("\n\nb: ");
        for (double val : b){
            System.out.print(val + " ");
        }
        System.out.println();
    }
}
