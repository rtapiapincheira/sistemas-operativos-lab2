#include <Exception.h>
#include <SolverThread.h>

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class F1 : public Function {
public:
    virtual double evaluate(double x) {
        return 1;
        double x2 = x*x;
        return x2*x * ::exp(x2);
    }
};

class MainSolver : public SolverThread {
private:
    int m_nThreads;

public:
    MainSolver(int nThreads, double x1, double x2, Function *f,
            double step = 1e-6) :
        SolverThread(x1, x2, f, step), m_nThreads(nThreads)
    {

    }

    virtual void run() {
        std::vector<SolverThread> solvers;
        double span = (m_x2 - m_x1) / m_nThreads;
        for (int i = 0; i < m_nThreads; i++) {
            double a = m_x1 + i * span;
            double b = m_x1 + (i+1) * span;
            solvers.push_back(SolverThread(a, b, m_f, m_step));
        }
        for (int i = 0; i < m_nThreads; i++) {
            solvers[i].start();
        }
        m_result = 0.0;
        for (int i = 0; i < m_nThreads; i++) {
            solvers[i].join();
            m_result += solvers[i].getResult();
        }
    }
};

int main() {
    F1 myFunction;
    MainSolver rt(4, -1000.0, 1000.0, &myFunction, 1e-6);
    try {
        rt.start();
        rt.join();
        cout << "result:" << rt.getResult() << endl;
    } catch (Exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}

