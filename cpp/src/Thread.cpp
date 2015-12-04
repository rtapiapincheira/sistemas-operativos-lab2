#include <Thread.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

Thread::Thread(Runnable *runnable) :
    m_runnable(runnable)
{
}

Thread::~Thread() {
}

void Thread::run() {
    // This is expected to be overriden by subclasses, if not, maybe run the
    // argument supplied through constructor. Otherwise it's a silly Thread use.
    if (m_runnable) {
        m_runnable->run();
    } else {
        printf("Bad thread usage, use a Runnable as argument or extend from this class.\n");
        exit(1);
    }
}

void Thread::sleep(_llint millis) {
    ::usleep((useconds_t)(millis*1000));
}

void* __internalThreadFunction(void *param) {
    if (param) {
        PThread *t = (PThread*)param;
        t->run();
    }
    return NULL;
}

PThread::PThread(Runnable *runnable) :
    Thread(runnable)
{
}

PThread::~PThread() {
}

void PThread::start() {
    int ret = pthread_create(&m_thread, NULL, __internalThreadFunction, this);
    if (ret != 0) {
        printf("Thread creation failed (%d)\n", ret);
        exit(1);
    }
}

void PThread::join() {
    int ret = pthread_join(m_thread, NULL);
    if (ret != 0) {
        printf("Thread join failed (%d)\n", ret);
        exit(1);
    }
}

ComputingThread::ComputingThread(double a, double h, int i, int n, Function *f, int step) :
    m_a(a),
    m_h(h),
    m_i(i),
    m_n(n),
    m_f(f),
    m_result(0),
    m_step(step)
{
}
ComputingThread::~ComputingThread() {}

void ComputingThread::run() {
    m_result = 0;
    for (int i = m_i; i <= m_n; i += m_step) {
        double x_i = m_h * i + m_a;
        m_result += m_f->evaluate(x_i);
    }
}

double ComputingThread::getResult() {
    return m_result;
}

