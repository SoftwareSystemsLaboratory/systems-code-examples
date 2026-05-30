#ifndef SEMAPHORE_HH
#define SEMAPHORE_HH

#include "mutex.hh"

class Semaphore {
public:
    Semaphore(int initial_value);
    ~Semaphore();
    void up();
    bool down();
private:
    Mutex *_lock;
    volatile int _count;
};

#endif
