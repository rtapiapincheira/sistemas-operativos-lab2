#ifndef __MUTEX_H_
#define __MUTEX_H_

#include <pthread.h>

#define _UNUSED(x) ((void*)&x)

/**
 * @brief The Mutex class provides mutual exclusion access to shared resources
 * queried by different threads. Here is the
 *
 * The methods lock, unlock and tryLock are atomic operations that allow to
 * synchronize different threads by means of blocking them while the lock is
 * being held by another thread.
 *
 * This implementation is a wrapper of the pthread mutexes and provides an OO
 * oriented mutex solution, besides, it allows to inject more generic logic
 * (useful for the problem domain).
 */
class Mutex {
private:
    pthread_mutex_t m_mutex;

public:
    /**
     * @brief Mutex Builds and initializes a new Mutex.
     */
    Mutex();

    /**
     * @brief ~Mutex Deallocates resources allocated by this class and destroys
     * the underlying mutex.
     */
    ~Mutex();

    /**
     * @brief lock
     */
    void lock();

    /**
     * @brief unlock
     */
    void unlock();

    bool tryLock();
};

class MutexLocker {
private:
    Mutex *m_mutex;

public:
    MutexLocker(Mutex *mutex);
    ~MutexLocker();
};

#endif // __MUTEX_H_
