#include <Mutex.h>
#include <Thread.h>

#include <iostream>
using namespace std;

Mutex myMutex;

int myGlobalVariable = 0;

class RunnerThread : public Thread {
public:
    void run() {
        //myMutex.lock();
        for (int j = 0; j < 6; j++) {
            cout << "RunnerThread(" << j << "), Asignando j=" << j << " a myGlobalVariable" << flush << endl;
            myGlobalVariable = j;
            cout << "RunnerThread(" << j << "), Valor de myGlobalVariable:" << myGlobalVariable << flush  << endl;
        }
        //myMutex.unlock();
    }
};

class ProcessRunnable : public Runnable {
public:
    virtual void run() {
        //myMutex.lock();
        for (int i = 0; i < 6; i++) {
            cout << "ProcessRunnable(" << i << "), Asignando i=" << i << " a myGlobalVariable" << flush << endl;
            myGlobalVariable = i;
            cout << "ProcessRunnable(" << i << "), Valor de myGlobalVariable:" << myGlobalVariable << flush << endl;
        }
        //myMutex.unlock();
    }
};


int main() {

    ProcessRunnable pr;
    Thread _rt(&pr);
    _rt.start();

    RunnerThread rt;
    rt.start();

    _rt.join();
    rt.join();

    return 0;
}

