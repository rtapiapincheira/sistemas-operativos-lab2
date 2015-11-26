#include <OThread.h>

OThread::OThread(Runnable *runnable) :
    Thread(runnable)
{

}

OThread::~OThread() {
}

void OThread::start() {
}

void OThread::join() {
}
