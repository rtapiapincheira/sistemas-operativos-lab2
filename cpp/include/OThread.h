#ifndef __OTHREAD_H_
#define __OTHREAD_H_

#include <Thread.h>

class OThread : public Thread {
private:
public:
    OThread(Runnable *runnable = NULL);

    virtual ~OThread();

    virtual void start();

    virtual void join();
};

#endif // __OTHREAD_H_
