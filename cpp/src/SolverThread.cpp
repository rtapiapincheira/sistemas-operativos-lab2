#include <SolverThread.h>

SolverThread::SolverThread(double a, double h, int i, int n, Function *f, int step) :
    m_a(a),
    m_h(h),
    m_i(i),
    m_n(n),
    m_f(f),
    m_result(0),
    m_step(step)
{
}

void SolverThread::run() {
    m_result = 0;
    for (int i = m_i; i < m_n; i += m_step) {
        double x_i = m_h * i + m_a;
        m_result += m_f->evaluate(x_i);
    }
}

double SolverThread::getResult() {
    return m_result;
}
