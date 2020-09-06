#include "semaphore.hh"
#include "debug.hh"
#include <stdio.h>
#include <pthread.h>

Semaphore::Semaphore(int initialValue) {
    _lock = new Mutex();
    _count = initialValue;
}

Semaphore::~Semaphore() {
    delete _lock;
}

void Semaphore::Up() {
    _lock->Lock();
    _count += 1;
    _lock->Unlock();
}

bool Semaphore::Down() {
    bool success = false;
    _lock->Lock();
    if(_count > 0) {
        _count -= 1;
        success = true;
    }
    _lock->Unlock();
    return success;
}


