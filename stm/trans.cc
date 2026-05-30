#include "trans.hh"
#include <stdio.h>

MemHandle::MemHandle(int value, int event)
{
    this->value = value;
    _event = event;
}

int MemHandle::get_event()
{
    return _event;
}

Transaction::Transaction(volatile int *value)
{
    _value = value;
    _event = 0;
    _rollbacks = 0;
    _lock = new Mutex();
}

Transaction::~Transaction()
{
    delete _lock;
}

int Transaction::get_rollback_count()
{
    return _rollbacks;
}

MemHandle* Transaction::begin()
{
    MemHandle* handle;
    _lock->lock();
    handle = new MemHandle(*_value, _event);
    _lock->unlock();
    return handle;
}

bool Transaction::try_commit(MemHandle* value)
{
    bool success = false;
    _lock->lock();
    if(_event == value->get_event())
    {
        *_value = value->value;
        _event += 1;
        success = true;
    }
    else
    {
        _rollbacks += 1;
    }
    _lock->unlock();
    delete value;
    return success;
}
