#include <Mutex.h>

#include <cstdio>

// --------- Mutex implementation
Mutex::Mutex() {
    if(pthread_mutex_init(&m_mutex, NULL)) {

    }
}
Mutex::~Mutex() {
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock() {
    pthread_mutex_lock(&m_mutex);

}
void Mutex::unlock() {
    pthread_mutex_unlock(&m_mutex);
}

bool Mutex::tryLock() {
    //printf("trying to lock\n");
    //fflush(stdout);
    return (pthread_mutex_trylock(&m_mutex) == 0 ? true : false);
}

// --------- MutexLocker implementation

MutexLocker::MutexLocker(Mutex *mutex) {
    m_mutex = mutex;
    if (m_mutex) {
        m_mutex->lock();
    }
}

MutexLocker::~MutexLocker() {
    if (m_mutex) {
        m_mutex->unlock();
    }
}
