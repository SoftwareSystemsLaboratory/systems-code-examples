#include "lock.hh"
#include <pthread.h>

unsigned long test_and_set(unsigned long *lock) {
    unsigned long newval = 0;
    asm volatile ("lock; cmpxchgl %2, %0"
                  : "+m" (*lock), "+a" (newval)	/* output operands */
                  : "r" (1)			/* input operands  */
                  : "cc");			/* clobbered registers */
    /* ("memory" means registers get flushed) */
    return newval;
}

void spin_lock(unsigned long *lock) {
    while(test_and_set(lock) == 1) {
        pthread_yield();
    }
}

void spin_unlock(unsigned long *lock) {
    *lock = 0;
}

