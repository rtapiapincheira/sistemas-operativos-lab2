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
