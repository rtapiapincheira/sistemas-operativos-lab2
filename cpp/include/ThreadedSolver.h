#ifndef __THREADEDSOLVER_H_
#define __THREADEDSOLVER_H_

#include <Solver.h>

/**
 * @brief The MainSolver class handles the creation and collection of child
 * threads.
 */
class ThreadedSolver : public Solver {
private:
public:

    /**
     * @brief MainSolver constructs a new MainSolver instance, by assigning the
     * integral parameters into local instance variables.
     */
    ThreadedSolver(double a, double b, double h, int n, Function *f);

    ~ThreadedSolver();

    /**
     * @brief executeThreads Creates, spawns, collects and calculates the final
     * integral result.
     * @return double, with the 3/8 simpson compound rule integral result.
     */
    virtual double executeProcessing();
};

#endif // __THREADEDSOLVER_H_
