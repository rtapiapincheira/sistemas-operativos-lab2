package cl.usach.so;

import java.util.ArrayList;

/**
 * @brief The MainSolver class handles the creation and collection of child
 * threads.
 */
public class MainSolver {

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
        solvers.add(new SolverThread(a, h, 1, n-2, f, 3)); factors.add(3.0);
        solvers.add(new SolverThread(a, h, 2, n-1, f, 3)); factors.add(3.0);
        solvers.add(new SolverThread(a, h, 3, n-3, f, 3)); factors.add(2.0);

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