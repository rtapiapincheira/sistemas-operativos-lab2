#include <Thread.h>

#include <unistd.h>
#include <stdio.h>

#include <Exception.h>

void* __internalThreadFunction(void *param) {
    if (param) {
        Thread *t = (Thread*)param;
        t->run();
    }
    return NULL;
}

Thread::Thread(Runnable *runnable) :
    m_runnable(runnable)
{
}

Thread::~Thread() {
}

void Thread::start() {
    int ret = pthread_create(&m_thread, NULL, __internalThreadFunction, this);
    if (ret != 0) {
        throw Exception::build("Thread creation failed", ret);
    }
}

void Thread::run() {
    // This is expected to be overriden by subclasses, if not, maybe run the
    // argument supplied through constructor. Otherwise it's a silly Thread use.
    if (m_runnable) {
        m_runnable->run();
    }
}

void Thread::join() {
    int ret = pthread_join(m_thread, NULL);
    if (ret != 0) {
        throw Exception::build("Thread join failed", ret);
    }
}

void Thread::sleep(_llint millis) {
    ::usleep((useconds_t)(millis*1000));
}
