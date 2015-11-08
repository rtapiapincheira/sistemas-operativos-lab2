#include <SolverThread.h>

//#include <iostream>
//using namespace std;

SolverThread::SolverThread(double x1, double x2, Function *f, double step) :
    m_x1(x1),
    m_x2(x2),
    m_f(f),
    m_step(step),
    m_result(0.0)
{
//    cout << "from " << x1 << " to " << x2 << "(by step " << step << ")" << endl;
}

void SolverThread::run() {
    m_result = 0.0;
    double x = m_x1;
    while(x < m_x2) {
        double y = m_f->evaluate(x);
        m_result += y * m_step;
        x += m_step;
    }
}

double SolverThread::getResult() {
    return m_result;
}
