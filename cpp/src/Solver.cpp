#include <Solver.h>

Solver::Solver(double a, double b, double h, int n, Function *f) :
    m_a(a),
    m_b(b),
    m_h(h),
    m_n(n),
    m_f(f)
{
}

Solver::~Solver() {

}
