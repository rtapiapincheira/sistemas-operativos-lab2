#ifndef __SOLVER_H_
#define __SOLVER_H_

#include <Function.h>

/**
 * @brief The MainSolver class handles the creation and collection of child
 * threads.
 */
class Solver {
protected:
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
    Solver(double a, double b, double h, int n, Function *f);

    ~Solver();

    /**
     * @brief executeThreads Creates, spawns, collects and calculates the final
     * integral result.
     * @return double, with the 3/8 simpson compound rule integral result.
     */
    virtual double executeProcessing() = 0;
};

#endif // __SOLVER_H_
