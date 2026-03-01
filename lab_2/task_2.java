import java.util.Arrays;

public class task_2 {
    static final double[] curX = {0, 0, 0, 0};
    static final double[] lastX = {0, 0, 0, 0};
    static double sigma = 0;
    static double eps = 1E-3;
    static int k = 0;
    
    static final double[][] a = {{5.554, 0.252, 0.496, 0.237}, 
                                {0.580, 4.953, 0.467, 0.028}, 
                                {0.319, 0.372, 8.935, 0.520}, 
                                {0.043, 0.459, 0.319, 4.778}};
    
    static final double[] b = {0.442, 0.464, 0.979, 0.126};

    static void calculationCurX(){
        // double sigma = 0;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (j != i){
                    sigma += a[i][j] * lastX[j];
                }
            }
            curX[i] = (1 / a[i][i]) * (b[i] - sigma);
            sigma = 0;
        }
    }

    static double checkEnd(){
        return Arrays.stream(new double[]{Math.abs(curX[1] - lastX[1]), 
                        Math.abs(curX[1] - lastX[1]),
                        Math.abs(curX[1] - lastX[1]), 
                        Math.abs(curX[1] - lastX[1])}).max().getAsDouble();
    }

    static void rewrite(){
        for (int i = 0; i < 4; i++){
            lastX[i] = curX[i];
        }
    }

    static void print(double E){
        System.out.printf("| %d |", k);
        for (int i = 0; i < 4; i++){
            System.out.printf("%.15f | ", curX[i]);
        }
        System.out.printf("%.4f%n", E);
        k++;
    }

    static void checkRes(){
        sigma = 0;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                sigma += a[i][j] * curX[j];
            }
            System.out.printf("Res for %d, equation: %.15f | b_1 = %.15f | dif = %.15f%n", i+1, sigma, b[i], Math.abs(sigma - b[i]));
        }
    }

    public static void main(String[] args){
        System.out.printf("| %-1s | %-16s | %-17s | %-17s | %-17s | %-10s%n", "k", "x1", "x2", "x3", "x4", "delta");
        print(checkEnd());
        calculationCurX();
        print(checkEnd());
        do {
            rewrite();
            calculationCurX();
            print(checkEnd());
        } while(checkEnd() > eps);
        System.out.printf("%n");
        checkRes();
    }
}