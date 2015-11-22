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

    public static void main(String[] args) {

        Options options = new Options();
        if (!options.parse(args)) {
            // return;
        }

        Scanner scanner = new Scanner(System.in);

        // Take all the parameters from the input
        double a, b;
        int N;
        int fx;
        int _realN;

        // ------ lower limit input -----
        System.out.print("Ingrese a: ");
        if (options.isASet) {
            a = options.a;
            System.out.println(a);
        } else {
            a = scanner.nextDouble();
        }

        // ------ upper limit input -----
        System.out.print("Ingrese b: ");
        if (options.isBSet) {
            b = options.b;
            System.out.println(b);
        } else {
            b = scanner.nextDouble();
        }

        // ------ number of partitions input -----
        System.out.print("Ingrese N: ");
        if (options.isNumPartitionsSet) {
            N = options.numPartitions;
            System.out.println(N);
        } else {
            N = scanner.nextInt();
        }
        _realN = 3 * N;

        System.out.printf("Seleccione la funcion a integrar (1 - %d):%n", functions.length);
        for (int i = 0; i < functions.length; i++) {
            System.out.printf("   opcion #%d: %s%n", i, functions[i].getName());
        }

        // ------ function index input ------
        if (options.isFxSet) {
            System.out.print(" ingrese la opcion: ");
            fx = options.fx;
            System.out.println(fx);
        } else {
            do {
                System.out.print(" ingrese la opcion: ");
                fx = scanner.nextInt();
            } while (fx < 0 || fx >= functions.length);
        }

        System.out.println();

        // ----- begin to calculate the final results -----

        double h = (b - a) / _realN;

        System.out.println("Resultado Integracion:");
        System.out.println("==========================");
        System.out.println();

        System.out.printf("Funcion a integrar      : %s%n", functions[fx].getName());
        System.out.printf("Numero de particiones   : 3 * (N=%d) = %d%n", N, _realN);
        System.out.printf("Limite inferior         : %.6f%n", a);
        System.out.printf("Limite superior         : %.6f%n", b);
        System.out.printf("Paso (h = (b-a)/N)      : %.6f%n", h);

        // ----- solve and print the final result -----------

        MainSolver solver = new MainSolver(a, b, h, _realN, functions[fx]);
        double result = solver.executeThreads();
        System.out.printf("Resultado de integracion: %.9f%n", result);
    }
}
