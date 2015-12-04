#ifndef __OPENMPSOLVER_H_
#define __OPENMPSOLVER_H_

#include <Solver.h>

class OpenmpSolver : public Solver {
public:
    OpenmpSolver(double a, double b, double h, int n, Function *f);

    virtual ~OpenmpSolver();

    virtual double executeProcessing();

private:
    double x_i(int i);
};

#endif // __OPENMPSOLVER_H_
