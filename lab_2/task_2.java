import java.util.Arrays;

public class task_2 {
    static final double[] curX = {0, 0, 0, 0};
    static final double[] lastX = {0, 0, 0, 0};
    double sigma = 0;
    
    static final double[][] a = {{5.554, 0.252, 0.496, 0.237}, 
                                {0.580, 4.953, 0.467, 0.028}, 
                                {0.319, 0.372, 8.935, 0.520}, 
                                {0.043, 0.459, 0.319, 4.778}};
    
    static final double[] b = {0.442, 0.464, 0.979, 0.126};

    void calculationCurX(){
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
        double delta = Arrays.stream({Math.abs(curX[1] - lastX[1]), 
                        Math.abs(curX[1] - lastX[1]),
                        Math.abs(curX[1] - lastX[1]), 
                        Math.abs(curX[1] - lastX[1])}).max().getAsDouble();
        return delta;
    }

    public static void main(String[] args){
        
    }
}