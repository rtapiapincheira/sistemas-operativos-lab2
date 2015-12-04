#include <OpenmpSolver.h>

OpenmpSolver::OpenmpSolver(double a, double b, double h, int n, Function *f) :
    Solver(a, b, h, n, f)
{
}

OpenmpSolver::~OpenmpSolver() {

}

double OpenmpSolver::executeProcessing() {
    double s = 0;

    // Doing some re-arrangements on the limits and the mute variable of the sum
    // we can end up with just a single sum

    s += m_f->evaluate(m_a);
    s += m_f->evaluate(m_b);

    s += 2 * (
        m_f->evaluate(m_n-1) +
        m_f->evaluate(m_n-2) +
        m_f->evaluate(m_n-3)
    );

#pragma omp parallel private(i) shared(s)
    {
        for (int i = 1; i <= m_n-2; i += 3) {
            s += 3 * m_f->evaluate(x_i(i));
            s += 3 * m_f->evaluate(x_i(i+1));
            s += 2 * m_f->evaluate(x_i(i+2));
        }
    }

    return (3 * m_h * s) / 8.0;
}

double OpenmpSolver::x_i(int i) {
    return (m_a + i * m_h);
}
