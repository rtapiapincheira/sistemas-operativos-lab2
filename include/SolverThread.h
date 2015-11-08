#ifndef __SOLVER_THREAD_H_
#define __SOLVER_THREAD_H_

#include <Thread.h>
#include <Function.h>

class SolverThread : public Thread {
protected:
    double m_x1;
    double m_x2;
    Function *m_f;
    double m_step;
    double m_result;

public:
    SolverThread(double x1, double x2, Function *f, double step = 1e-6);

    virtual void run();

    double getResult();
};

#endif // __SOLVER_THREAD_H_
