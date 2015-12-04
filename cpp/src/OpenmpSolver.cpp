#include <OpenmpSolver.h>

OpenmpSolver::OpenmpSolver(double a, double b, double h, int n, Function *f) :
    Solver(a, b, h, n, f)
{
}

OpenmpSolver::~OpenmpSolver() {

}

double OpenmpSolver::executeProcessing() {
    double s = 0;
    double x1, x2, x3, y1, y2, y3;
    double n = m_n;
    int i;

    // Doing some re-arrangements on the limits and the mute variable of the sum
    // we can end up with just a single sum

    s += m_f->evaluate(m_a);
    s += m_f->evaluate(m_b);

    s += 2 * (
        m_f->evaluate(m_n-1) +
        m_f->evaluate(m_n-2) +
        m_f->evaluate(m_n-3)
    );

#pragma omp parallel shared( s, n ) private ( x1, x2, x3, y1, y2, y3 )
{
    #pragma omp for reduction ( + : s )
    for(i=1; i<n-3; i+=3) {
        x1 = x_i(i);
        x2 = x_i(i+1);
        x3 = x_i(i+2);
        y1 = m_f->evaluate(x1);
        y2 = m_f->evaluate(x2);
        y3 = m_f->evaluate(x3);
        s += 3 * y1;
        s += 3 * y2;
        s += 2 * y3;
    }
}
    return (3 * m_h * s) / 8.0;
}

double OpenmpSolver::x_i(int i) {
    return (m_a + i * m_h);
}
