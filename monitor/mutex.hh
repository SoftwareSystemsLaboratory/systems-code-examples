#ifndef MUTEX_HH
#define MUTEX_HH

class Mutex {
public:
    Mutex();
    ~Mutex();
    void lock();
    void unlock();
private:
    unsigned long test_and_set(unsigned long *lock);
    unsigned long _lock;
};
#endif

