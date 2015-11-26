#include <PThread.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
