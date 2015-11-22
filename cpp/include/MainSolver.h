#ifndef __MAINSOLVER_H_
#define __MAINSOLVER_H_

#include <Function.h>

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
    MainSolver(double a, double b, double h, int n, Function *f);

    /**
     * @brief executeThreads Creates, spawns, collects and calculates the final
     * integral result.
     * @return double, with the 3/8 simpson compound rule integral result.
     */
    double executeThreads();
};

#endif // __MAINSOLVER_H_
