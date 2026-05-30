#ifndef MONITOR_HH
#define MONITOR_HH

#include "mutex.hh"

class Monitor {
public:
    Monitor();
    ~Monitor();
    void enter();
    void exit();
    void wait();
    void pulse();
private:
    Mutex *_lock;
    volatile bool _locked;
    volatile int _pulse;
};

#endif
