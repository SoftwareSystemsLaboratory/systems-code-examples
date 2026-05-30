#ifndef TRANS_HH
#define TRANS_HH

#include "mutex.hh"

class MemHandle {
public:
    MemHandle(int value, int event);
    int value;
    int get_event();
private:
    int _event;
};

class Transaction {
public:
    Transaction(volatile int* value);
    ~Transaction();
    bool try_commit(MemHandle* value);
    MemHandle* begin();
    int get_rollback_count();
private:
    Mutex* _lock;
    volatile int* _value;
    int _event;
    int _rollbacks;
};

#endif
