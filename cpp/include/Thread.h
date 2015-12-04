#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread/pthread.h>
//#include <pthread.h>

#include <Function.h>

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

public:
    /**
     * @brief Thread constructs a new instance for running an independent
     * thread.
     * @param runnable Optional memory address of a Runnable instance.
     */
    Thread(Runnable *runnable = 0);

    virtual ~Thread();

    /**
     * @brief start Starts the thread represented by this object.
     */
    virtual void start() = 0;

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
    virtual void join() = 0;

    /**
     * @brief sleep Waits at least millis seconds before returning.
     *
     * @param millis number of milliseconds to wait, at least.
     */
    static void sleep(_llint millis);
};

class PThread : public Thread {
private:
    pthread_t m_thread;

public:
    PThread(Runnable *runnable = NULL);

    virtual ~PThread();

    virtual void start();

    virtual void join();
};

/**
 * @brief The SolverThread class represents an integral to be solved in a
 * separate thread.
 */
class ComputingThread : public PThread {
protected:
    // Lower limit for the integral to solver
    double m_a;

    // Step for consecutive x_i (x_{i+1} - x_i)
    double m_h;

    // Start for the index to be calculated by this class
    int m_i;

    // End index for this sum to reach
    int m_n;

    // Function to integrate
    Function *m_f;

    // Final result this integral calculated
    double m_result;

    // Offset for the indexes (i.e. i += m_step)
    int m_step;

public:
    ComputingThread(double m_a, double m_h, int m_i, int m_n, Function *f, int step);

    ~ComputingThread();

    virtual void run();

    double getResult();
};

#endif // __THREAD_H_
