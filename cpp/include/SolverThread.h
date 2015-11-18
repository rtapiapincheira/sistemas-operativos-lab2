#ifndef __SOLVER_THREAD_H_
#define __SOLVER_THREAD_H_

#include <Thread.h>
#include <Function.h>

/**
 * @brief The SolverThread class represents an integral to be solved in a
 * separate thread.
 */
class SolverThread : public Thread {
protected:
    // Lower limit for the integral to solver
    double m_a;

    // Step for consecutive x_i (x_{i+1} - x_i)
    double m_h;

    // Start for the index to be calculated by this class
    int m_i;

    // End index for this sum to reach
    int m_n;

    // Function to integrate
    Function *m_f;

    // Final result this integral calculated
    double m_result;

    // Offset for the indexes (i.e. i += m_step)
    int m_step;

public:
    SolverThread(double m_a, double m_h, int m_i, int m_n, Function *f, int step);

    virtual void run();

    double getResult();
};

#endif // __SOLVER_THREAD_H_
