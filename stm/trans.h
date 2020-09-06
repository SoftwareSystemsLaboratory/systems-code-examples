#ifndef TRANS_HH
#define TRANS_HH

#include "mutex.hh"

class MemHandle {
public:
    MemHandle(int value, int event);
    int Value;
    int getEvent();
private:
    int _event;
};

class Transaction {
public:
    Transaction(volatile int* value);
    ~Transaction();
    bool TryCommit(MemHandle* value);
    MemHandle* Begin();
    int GetRollbackCount();
private:
    Mutex* _lock;
    volatile int* _value;
    int _event;
    int _rollbacks;
};

#endif
