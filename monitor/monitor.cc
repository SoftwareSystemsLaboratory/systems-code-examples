#include "monitor.hh"
#include <stdio.h>
#include <pthread.h>

Monitor::Monitor()
{
    _lock = new Mutex();
    _locked = false;
    _pulse = 0;
}

Monitor::~Monitor()
{
    delete _lock;
}

void Monitor::enter()
{
    _lock->lock();
    _locked = true;
}

void Monitor::exit()
{
    _locked = false;
    _lock->unlock();
}

void Monitor::wait()
{
    if(!_locked)
    {
        fprintf(stderr, "wait called wait without a lock\n");
    }
    while(_pulse == 0)
    {
        exit();
        pthread_yield();
        enter();
    }
    _pulse -= 1;
}

void Monitor::pulse()
{
    if(!_locked)
    {
        fprintf(stderr, "pulse called without a lock\n");
    }
    _pulse += 1;
}
