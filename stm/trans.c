#include "trans.hh"
#include <stdio.h>

MemHandle::MemHandle(int value, int event) {
    Value = value;
    _event = event;
}

int MemHandle::getEvent() {
    return _event;
}

Transaction::Transaction(volatile int *value) {
    _value = value;
    _event = 0;
    _rollbacks = 0;
    _lock = new Mutex();
}

Transaction::~Transaction() {
    delete _lock;
}

int Transaction::GetRollbackCount() {
    return _rollbacks;
}

MemHandle* Transaction::Begin() {
    MemHandle* handle;
    _lock->Lock();
    handle = new MemHandle(*_value, _event);
    _lock->Unlock();
    return handle;
}

bool Transaction::TryCommit(MemHandle* value) {
    bool success = false;
    _lock->Lock();
    if(_event == value->getEvent()) {
        *_value = value->Value;
        _event += 1;
        success = true;
    } else {
        _rollbacks += 1;
    }
    _lock->Unlock();
    delete value;
    return success;
}

