package cl.usach.so;

/**
 * @brief The SolverThread class represents an integral to be solved in a separate thread.
 */
public class SolverThread extends Thread {

    // Lower limit for the integral to solve
    protected double a;

    // Step for consecutive x_i (x_{i+1} - x_i)
    protected double h;

    // Start for the index to be calculated by this class
    protected int i;

    // End index for this sum to reach
    protected int n;

    // Function to integrate
    protected Function f;

    // Final result this integral calculated
    protected double result;

    // Offset for the indexes (i.e. i += m_step)
    protected int step;


    public SolverThread(double a, double h, int i, int n, Function f, int step) {
        this.a = a;
        this.h = h;
        this.i = i;
        this.n = n;
        this.f = f;
        this.step = step;
    }

    @Override
    public void run() {
        result = 0.0;
        for (int i = this.i; i < n; i += step) {
            double xi = (h * i) + a;
            result += f.evaluate(xi);
        }
    }

    double getResult() {
        return result;
    }
}
