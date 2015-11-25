#include <MainSolver.h>

#include <SolverThread.h>

#include <vector>

MainSolver::MainSolver(double a, double b, double h, int n, Function *f) :
    m_a(a),
    m_b(b),
    m_h(h),
    m_n(n),
    m_f(f)
{
}
#include <iostream>
double MainSolver::executeThreads() {
    std::vector<SolverThread> solvers;
    std::vector<double> factors;

    // each of the sums will be a separate thread, with a corresponding
    // factor for which the whole sum will weigh.

    std::cout << m_f->getName() << std::endl;

    solvers.push_back(SolverThread(m_a, m_h, 1, m_n-2, m_f, 3)); factors.push_back(3.0);
    solvers.push_back(SolverThread(m_a, m_h, 2, m_n-1, m_f, 3)); factors.push_back(3.0);
    solvers.push_back(SolverThread(m_a, m_h, 3, m_n-3, m_f, 3)); factors.push_back(2.0);

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
