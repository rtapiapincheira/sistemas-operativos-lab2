using System;
using System.Collections;
using System.Threading;

/**
 * Thread a-la-Java.
 */
public abstract class MyThread {
	
	private Thread mThread;
	
	public MyThread() {
		mThread = new Thread(Run);
	}
	
	public void Start() {
		mThread.Start();
	}
	
	public void Join() {
		mThread.Join();
	}
	
	public abstract void Run();
}

/**
 * @brief The Function class represents a formula which will be used along with the integration threads.
 */
public abstract class Function {
	private String name;
	
	public Function(String name) {
		this.name = name;
	}
	
	/**
     * @brief evaluate Definition of the formula.
     * @param x X coordinate to evalue for this function formlua.
     * @return Double, with the Y coordinate for this formula evaluated at x.
     */
	public abstract double evaluate(double x);
	
	/**
     * @brief getName Gets the name of the formula.
     */
	public String getName() {
		return name;
	}
}

/**
 * @brief The SolverThread class represents an integral to be solved in a separate thread.
 */
public class SolverThread : MyThread {

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
    
    public override void Run() {
		result = 0.0;
        for (int i = this.i; i < n; i += step) {
            double xi = (h * i) + a;
            result += f.evaluate(xi);
        }
    }
    
    public double GetResult() {
    	return result;
    }
}
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
        solvers.add(new SolverThread(a, h, 0, n, f, 3)); factors.add(3.0);
        solvers.add(new SolverThread(a, h, 1, n, f, 3)); factors.add(3.0);
        solvers.add(new SolverThread(a, h, 2, n, f, 3)); factors.add(2.0);

        // start every thread
        for (int i = 0; i < solvers.Count; i++) {
            solvers.get(i).Start();
        }

        // join every thread and afterwards collect its result
        double result = 0.0;
        for (int i = 0; i < solvers.Count; i++) {
            try {
                solvers.Get(i).Join();
            } catch (InterruptedException ie) {
                ie.printStackTrace();
                throw new RuntimeException(
                    "You shouldn't interrupt a blocking method, this is sure a programmer error, beware! ...");
            }
            result += (factors.Get(i) * solvers.Get(i).GetResult());
        }

        // evaluate the function at both ends
        result += f.evaluate(a);
        result += f.evaluate(b);

        // calculate the final result by using the weighing 3h/8
        return (3 * h * result / 8);
    }

}


public class F1 : Function {
	public F1() : base("x2") {
	}
	public override double evaluate(double x) {
		return x * x;
	}
}

public class WorkerThreadExample
{
    static void Main()
    {
    	F1 f = new F1();
    
    	SolverThread st = new SolverThread(0, 2.0/1000.0, 0, 1000, f, 1);
    	st.Start();
    	st.Join();
        double result = st.GetResult();
        Console.WriteLine("main thread: Worker thread has terminated {0}.", result);
    }
}