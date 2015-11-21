package cl.usach.so;

import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

/**
 * Main program.
 */
public class Main {

    static {
        Locale.setDefault(Locale.US);
    }

    /**
     * Definition of every function.
     */
    private static Function[] functions = {
        new Function("cos(x)") { // 0
            public double evaluate(double x) {return Math.cos(x);}
        },
        new Function("sin(x)") { // 1
            public double evaluate(double x) {return Math.sin(x);}
        },
        new Function("x2") { // 2
            public double evaluate(double x) {return Math.pow(x, 2);}
        },
        new Function("exp(x)") { // 3
            public double evaluate(double x) {return Math.exp(x);}
        },
        new Function("x2 exp(x)") { // 4
            public double evaluate(double x) {return Math.pow(x, 2) * Math.exp(x);}
        },
        new Function("7/4 x3 exp(x2) + 2x") { // 5
            public double evaluate(double x) {return 7.0/4 * Math.pow(x, 3) * Math.exp(Math.pow(x, 2)) + 2 * x;}
        },
        new Function("3x cos(4x) + 2") { // 6
            public double evaluate(double x) {return 3 * x + Math.cos(4 * x) + 2;}
        },
        new Function("2x") { // 7
            public double evaluate(double x) {return 2 * x;}
        },
        new Function("4 + x") { // 8
            public double evaluate(double x) {return 4 + x;}
        },
        new Function("2x2 + x + 6") { // 9
            public double evaluate(double x) {return 2 * Math.pow(x, 2) + x + 6;}
        }
    };

    /**
     * @brief The MainSolver class handles the creation and collection of child
     * threads.
     */
    private static class MainSolver {

        // Lower limit for the whole integral.
        private double a;

        // Upper limite for the whole integral.
        private double b;

        // Width of every interval of the whole interval.
        private double h;

        // Number of intervals in which each integral will be divided.
        private int n;

        // Function to integrate (take the address of one instance of the classes defined above).
        private Function f;

        /**
         * @brief MainSolver constructs a new MainSolver instance, by assigning the integral parameters into local
         * instance variables.
         */
        public MainSolver(double a, double b, double h, int n, Function f) {
            this.a = a;
            this.b = b;
            this.h = h;
            this.n = n;
            this.f = f;
        }

        /**
         * @brief executeThreads Creates, spawns, collects and calculates the final integral result.
         * @return double, with the 3/8 simpson compound rule integral result.
         */
        public double executeThreads() {
            ArrayList<SolverThread> solvers = new ArrayList<SolverThread>();
            ArrayList<Double> factors = new ArrayList<Double>();

            // each of the sums will be a separate thread, with a corresponding
            // factor for which the whole sum will weigh.
            solvers.add(new SolverThread(a, h, 0, n, f, 3)); factors.add(3.0);
            solvers.add(new SolverThread(a, h, 1, n, f, 3)); factors.add(3.0);
            solvers.add(new SolverThread(a, h, 2, n, f, 3)); factors.add(2.0);

            // start every thread
            for (int i = 0; i < solvers.size(); i++) {
                solvers.get(i).start();
            }

            // join every thread and afterwards collect its result
            double result = 0.0;
            for (int i = 0; i < solvers.size(); i++) {
                try {
                    solvers.get(i).join();
                } catch (InterruptedException ie) {
                    ie.printStackTrace();
                    throw new RuntimeException(
                        "You shouldn't interrupt a blocking method, this is sure a programmer error, beware! ...");
                }
                result += (factors.get(i) * solvers.get(i).getResult());
            }

            // evaluate the function at both ends
            result += f.evaluate(a);
            result += f.evaluate(b);

            // calculate the final result by using the weighing 3h/8
            return (3 * h * result / 8);
        }
    }

    public static void main(String[] args) {

        /*double a = 0;
        double b = 5;
        int N = 500000;
        int fx = 7;*/

        Scanner scanner = new Scanner(System.in);

        // Take all the parameters from the input
        double a, b;
        int N;
        int fx;

        // ------ lower limit input -----
        System.out.print("Ingrese a: ");
        a = scanner.nextDouble();

        // ------ upper limit input -----
        System.out.print("Ingrese b: ");
        b = scanner.nextDouble();

        // ------ number of partitions input -----
        System.out.print("Ingrese N: ");
        N = scanner.nextInt();

        System.out.printf("Seleccione la funcion a integrar (1 - %d):%n", functions.length);
        for (int i = 0; i < functions.length; i++) {
            System.out.printf("   opcion #%d: %s%n", i, functions[i].getName());
        }

        // ------ function index input ------
        do {
            System.out.print(" ingrese la opcion: ");
            fx = scanner.nextInt();
        } while (fx < 0 || fx >= functions.length);

        // ----- begin to calculate the final results -----

        double h = (b - a) / N;

        System.out.println("Resultado Integracion:");
        System.out.println("==========================");
        System.out.println();

        System.out.printf("Funcion a integrar      : %s%n", functions[fx].getName());
        System.out.printf("Numero de particiones   : 3 * (N=%d) = %d%n", N, 3 * N);
        System.out.printf("Limite inferior         : %.6f%n", a);
        System.out.printf("Limite superior         : %.6f%n", b);
        System.out.printf("Paso (h = (b-a)/N)      : %.6f%n", h);

        // ----- solve and print the final result -----------

        MainSolver solver = new MainSolver(a, b, h, N, functions[fx]);
        double result = solver.executeThreads();

        System.out.printf("Resultado de integracion: %.9f%n", result);
    }
}
