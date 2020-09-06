#include "mutex.hh"
#include <pthread.h>

Mutex::Mutex() {
    this->_lock = 0;
}

Mutex::~Mutex() {
}

void Mutex::Lock() {
    while(test_and_set(&this->_lock) == 1) {
        pthread_yield();
    }
}

unsigned long Mutex::test_and_set(unsigned long *lock) {
    unsigned long newval = 0;
    asm volatile ("lock; cmpxchgl %2, %0"
                  : "+m" (*lock), "+a" (newval)	/* output operands */
                  : "r" (1)			/* input operands  */
                  : "cc");			/* clobbered registers */
    return newval;
}

void Mutex::Unlock() {
    this->_lock = 0;
}

