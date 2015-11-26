#ifndef __PTHREAD_H_
#define __PTHREAD_H_

#include <Thread.h>
#include <pthread.h>

class PThread : public Thread {
private:
    pthread_t m_thread;

public:
    PThread(Runnable *runnable = NULL);

    virtual ~PThread();

    virtual void start();

    virtual void join();
};

#endif // __PTHREAD_H_
