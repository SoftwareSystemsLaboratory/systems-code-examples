#include "monitor.hh"
#include <stdio.h>
#include <pthread.h>

Monitor::Monitor() {
    _lock = new Mutex();
    _locked = false;
    _pulse = 0;
}

Monitor::~Monitor() {
    delete _lock;
}

void Monitor::Enter() {
    _lock->Lock();
    _locked = true;
}

void Monitor::Exit() {
    _locked = false;
    _lock->Unlock();
}

void Monitor::Wait() {
    if(!_locked) {
        fprintf(stderr, "wait called wait without a lock\n");
    }
    while(_pulse == 0) {
        Exit();
        pthread_yield();
        Enter();
    }
    _pulse -= 1;
}

void Monitor::Pulse() {
    if(!_locked) {
        fprintf(stderr, "pulse called without a lock\n");
    }
    _pulse += 1;
}

