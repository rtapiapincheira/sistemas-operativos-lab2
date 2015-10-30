#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>

typedef long long int _llint;

/**
 * @brief The Runnable class defines an interface for running a piece of code in
 * a separate thread.
 */
class Runnable {
public:
    virtual void run()=0;
};

/**
 * @brief The Thread class represents a lightweight process, with shared memory
 * useful to achieve paralelism and concurrency for applications.
 */
class Thread {
private:
    Runnable *m_runnable;
    pthread_t m_thread;

public:
    Thread(Runnable *runnable = NULL);
    ~Thread();

    void start();
    virtual void run();
    void join();

    static void sleep(_llint millis);
};

#endif // __THREAD_H_
