// Гаус

public class task_1 {
    static double[][] a = {{5.554, 0.252, 0.496, 0.237}, 
                           {0.580, 4.953, 0.467, 0.028}, 
                           {0.319, 0.372, 8.935, 0.520}, 
                           {0.043, 0.459, 0.319, 4.778}};

    static double[][] a_copy = {{5.554, 0.252, 0.496, 0.237}, 
                                {0.580, 4.953, 0.467, 0.028}, 
                                {0.319, 0.372, 8.935, 0.520}, 
                                {0.043, 0.459, 0.319, 4.778}};

    static double[] b = {0.442, 0.464, 0.979, 0.126};

    static double[] b_copy = {0.442, 0.464, 0.979, 0.126};

    static double[] x = {1, 1, 1, 1};

    static void compo(int i){
        for (int string = i + 1; string < 4; string++){
            double k = a[string][i] / a[i][i];
            b[string] = b[string] - b[i] * k;
            for (int j = 0; j < 4; j++){
                a[string][j] = a[string][j] - a[i][j] * k;
            }
        }
    }

    static void resX(){
        for (int i = 3; i >= 0; i--){
            double sum = 0;
            for (int j = 0; j < 4; j++){
                if (j != i) {
                    sum += a[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
        }
    }

    public static void main(String[] args){
        compo(0);
        compo(1);
        compo(2);
        resX();
        
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                System.out.print(a[i][j] + " ");
            }
            System.out.println(" | " + b[i]);
        }
        
        System.out.println();
        for (int i = 0; i < 4; i++){
            System.out.printf("%.10f%n", x[i]);
        }
        
        System.out.println();
        for (int i = 0; i < 4; i++){
            double result = a_copy[i][0] * x[0] + a_copy[i][1] * x[1] + a_copy[i][2] * x[2] + a_copy[i][3] * x[3];
            System.out.println(b_copy[i] + " | " + result);
        }
    }
}
