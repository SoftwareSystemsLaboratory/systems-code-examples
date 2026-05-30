#include "semaphore.hh"
#include "debug.hh"
#include <stdio.h>
#include <pthread.h>

Semaphore::Semaphore(int initial_value)
{
    _lock = new Mutex();
    _count = initial_value;
}

Semaphore::~Semaphore()
{
    delete _lock;
}

void Semaphore::up()
{
    _lock->lock();
    _count += 1;
    _lock->unlock();
}

bool Semaphore::down()
{
    bool success = false;
    _lock->lock();
    if(_count > 0)
    {
        _count -= 1;
        success = true;
    }
    _lock->unlock();
    return success;
}

