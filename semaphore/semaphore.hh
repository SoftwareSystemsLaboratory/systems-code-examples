#ifndef SEMAPHORE_HH
#define SEMAPHORE_HH

#include "mutex.hh"

class Semaphore {
public:
    Semaphore(int initialValue);
    ~Semaphore();
    void Up();
    bool Down();
private:
    Mutex *_lock;
    volatile int _count;
};

#endif

