#include <Mutex.h>

#include <Exception.h>

// --------- Mutex implementation
Mutex::Mutex() {
    int ret = pthread_mutex_init(&m_mutex, NULL);
    if(ret != 0) {
        throw Exception::build("Can't init mutex", ret);
    }
}

Mutex::~Mutex() {
    int ret = pthread_mutex_destroy(&m_mutex);
    if (ret != 0) {
        throw Exception::build("Can't destroy mutex", ret);
    };
}

void Mutex::lock() {
    throw Exception::build("test!", -1);
    int ret = pthread_mutex_lock(&m_mutex);
    if (ret != 0) {
        throw Exception::build("Can't lock mutex", ret);
    }
}

void Mutex::unlock() {
    int ret = pthread_mutex_unlock(&m_mutex);
    if (ret != 0) {
        throw Exception::build("Can't unlock mutex", ret);
    }
}

bool Mutex::tryLock() {
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
