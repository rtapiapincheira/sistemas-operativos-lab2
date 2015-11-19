#include <SolverThread.h>

#include <Options.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

/*#define LOWER_LIMIT    -1
#define UPPER_LIMIT    10
#define FX_INDEX       2
#define NUM_PARTITIONS 100000*/

// Maximum number of functions
#define MAX_FUNCTIONS 10

// Definition of every function
DEFINE_FORMULA(F0, "cos(x)", x, (::cos(x)));                                F0 __f0;
DEFINE_FORMULA(F1, "sin(x)", x, (::sin(x)));                                F1 __f1;
DEFINE_FORMULA(F2, "x2", x, (x * x));                                       F2 __f2;
DEFINE_FORMULA(F3, "exp(x)", x, (::exp(x)));                                F3 __f3;
DEFINE_FORMULA(F4, "x2 exp(x)", x, (x * x * ::exp(x)));                     F4 __f4;
DEFINE_FORMULA(F5, "7/4 x3 exp(x2) + 2x", x, (7*x*x*x/4*::exp(x*x)+2*x));   F5 __f5;
DEFINE_FORMULA(F6, "3x cos(4x) + 2", x, (3*x*::cos(4*x)+2));                F6 __f6;
DEFINE_FORMULA(F7, "2x", x, (2 * x));                                       F7 __f7;
DEFINE_FORMULA(F8, "4 + x", x, (4 + x));                                    F8 __f8;
DEFINE_FORMULA(F9, "2x2 + x + 6",x, (2 * x * x + x + 6));                   F9 __f9;

// We put all the instance address into an array for ease of iterating over
// them.
Function *functions[MAX_FUNCTIONS] = {
    &__f0,
    &__f1,
    &__f2,
    &__f3,
    &__f4,
    &__f5,
    &__f6,
    &__f7,
    &__f8,
    &__f9
};

/**
 * @brief The MainSolver class handles the creation and collection of child
 * threads.
 */
class MainSolver {
private:
    // Lower limit for the whole integral.
    double m_a;
    // Upper limite for the whole integral.
    double m_b;
    // Width of every interval of the whole interval.
    double m_h;
    // Number of intervals in which each integral will be divided.
    int m_n;
    // Function to integrate (take the address of one instance of the classes
    // defined above).
    Function *m_f;
public:

    /**
     * @brief MainSolver constructs a new MainSolver instance, by assigning the
     * integral parameters into local instance variables.
     */
    MainSolver(double a, double b, double h, int n, Function *f) :
        m_a(a),
        m_b(b),
        m_h(h),
        m_n(n),
        m_f(f)
    {
    }

    /**
     * @brief executeThreads Creates, spawns, collects and calculates the final
     * integral result.
     * @return double, with the 3/8 simpson compound rule integral result.
     */
    double executeThreads() {
        std::vector<SolverThread> solvers;
        std::vector<double> factors;

        // each of the sums will be a separate thread, with a corresponding
        // factor for which the whole sum will weigh.
        solvers.push_back(SolverThread(m_a, m_h, 0, m_n, m_f, 3)); factors.push_back(3);
        solvers.push_back(SolverThread(m_a, m_h, 1, m_n, m_f, 3)); factors.push_back(3);
        solvers.push_back(SolverThread(m_a, m_h, 2, m_n, m_f, 3)); factors.push_back(2);

        // start every thread
        for (size_t i = 0; i < solvers.size(); i++) {
            solvers[i].start();
        }

        // join every thread and afterwards collect its result
        double result = 0.0;
        for (size_t i = 0; i < solvers.size(); i++) {
            solvers[i].join();
            result += (factors[i] * solvers[i].getResult());
        }

        // evaluate the function at both ends
        result += m_f->evaluate(m_a);
        result += m_f->evaluate(m_b);

        // calculate the final result by using the weighing 3h/8
        return (3 * m_h * result / 8);
    }
};

int main(int argc, char **argv) {

    Options options;

    if (!options.parse(argc, argv)) {
        return 1;
    }

    // Take all the parameters from the input
    double a, b;
    int N;
    int fx;

    // ------ lower limit input -----
    std::cout << "Ingrese a: ";
#ifdef LOWER_LIMIT
    a = LOWER_LIMIT;
    std::cout << a << std::endl;
#else
    if (options.m_isASet) {
        a = options.m_a;
        std::cout << a << std::endl;
    } else {
        std::cin >> a;
    }
#endif

    // ------ upper limit input -----
    std::cout << "Ingrese b: ";
#ifdef UPPER_LIMIT
    b = UPPER_LIMIT;
    std::cout << b << std::endl;
#else
    if (options.m_isBSet) {
        b = options.m_b;
        std::cout << b << std::endl;
    } else {
        std::cin >> b;
    }
#endif

    // ------ number of partitions input -----
    std::cout << "Ingrese N: ";
#ifdef NUM_PARTITIONS
    N = NUM_PARTITIONS;
    std::cout << N << std::endl;
#else
    if (options.m_isNumPartitionsSet) {
        N = options.m_numPartitions;
        std::cout << N << std::endl;
    } else {
        std::cin >> N;
    }
#endif

    std::cout << "Seleccione la funcion a integrar (1 - " << MAX_FUNCTIONS << "):" << std::endl;
    for (int i = 0; i < MAX_FUNCTIONS; i++) {
        std::cout << "   opcion #" << i << ": " << functions[i]->getName() << std::endl;
    }

    // ------ function index input ------
#ifdef FX_INDEX
    fx = FX_INDEX;
    std::cout << " ingrese la opcion: " << fx << std::endl;
#else
    if (options.m_isFxSet) {
        std::cout << " ingrese la opcion: ";
        fx = options.m_fx;
        std::cout << fx << std::endl;
    } else {
        do {
            std::cout << " ingrese la opcion: ";
            std::cin >> fx;
        } while (fx < 0 || fx >= MAX_FUNCTIONS);
    }
#endif
    std::cout << std::endl;

    // ----- begin to calculate the final results -----

    double h = (b - a) / N;

    std::cout << "Resultado Integracion:" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << std::endl;

    std::cout << "Funcion a integrar      : " << functions[fx]->getName() << std::endl;
    std::cout << "Numero de particiones   : 3 * (N=" << N << ") = " << (3 * N) << std::endl;
    std::cout << "Limite inferior         : " << a << std::endl;
    std::cout << "Limite superior         : " << b << std::endl;
    std::cout << "Paso (h = (b-a)/N)      : " << std::setprecision(6) << h << std::endl;

    // ----- solve and print the final result -----------

    MainSolver solver(a, b, h, N, functions[fx]);

    double result = solver.executeThreads();
    std::cout << "Resultado de integracion: " << std::setprecision(9) << result << std::endl;

    return 0;
}

