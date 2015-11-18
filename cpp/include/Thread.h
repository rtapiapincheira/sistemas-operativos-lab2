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
    /**
     * @brief Pointer to an object that encapsulates the running logic of a
     * separate thread.
     */
    Runnable *m_runnable;
    pthread_t m_thread;

public:
    /**
     * @brief Thread constructs a new instance for running an independent
     * thread.
     * @param runnable Optional memory address of a Runnable instance.
     */
    Thread(Runnable *runnable = NULL);

    ~Thread();

    /**
     * @brief start Starts the thread represented by this object.
     */
    void start();

    /**
     * @brief run Logic to be run in a independant thread. By default, this runs
     * the Runnable instance if any. This method can be overriden by a subclass
     * that may contain the logic (so, there're two ways of defining new
     * threads).
     */
    virtual void run();

    /**
     * @brief join Blocking method that waits this thread to terminate.
     */
    void join();

    /**
     * @brief sleep Waits at least millis seconds before returning.
     *
     * @param millis number of milliseconds to wait, at least.
     */
    static void sleep(_llint millis);
};

#endif // __THREAD_H_
