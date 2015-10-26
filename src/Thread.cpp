#include <Thread.h>
#include <unistd.h>

#include <stdio.h>

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

/*void Thread::setDaemon(bool isDaemon) {
    m_isDaemon = isDaemon;
}*/

void Thread::start() {
    int ret = pthread_create(&m_thread, NULL, __internalThreadFunction, this);
    if (ret) {
        printf("Thread creation failed: %d\n", ret);
        return;
    }
    // llamar a pthread create y pasar

}
void Thread::run() {
    // This is expected to be overriden by subclasses, if not, maybe run the
    // argument supplied through constructor. Otherwise it's a silly Thread use.
    if (m_runnable) {
        m_runnable->run();
    }
}
void Thread::join() {
    pthread_join(m_thread, NULL);
}

/*void Thread::requestStop() {

}

bool Thread::isRunning() {

}

bool Thread::isDead() {

}*/

void Thread::sleep(_llint millis) {
    ::usleep((useconds_t)(millis*1000));
}
