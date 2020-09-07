#ifndef MONITOR_HH
#define MONITOR_HH

#include "mutex.hh"

class Monitor {
public:
    Monitor();
    ~Monitor();
    void Enter();
    void Exit();
    void Wait();
    void Pulse();
private:
    Mutex *_lock;
    volatile bool _locked;
    volatile int _pulse;
};

#endif

