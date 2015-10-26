#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>

typedef long long int _llint;

class Runnable {
public:
    virtual void run()=0;
};

class Thread {
private:
    Runnable *m_runnable;
    bool m_shouldStop;

    pthread_t m_thread;

    bool m_isDaemon;

public:
    Thread(Runnable *runnable = NULL);
    ~Thread();

    void start();
    virtual void run();
    void join();

    /*void requestStop();
    bool isRunning();
    bool isDead();*/

    static void sleep(_llint millis);
};

#endif // __THREAD_H_
