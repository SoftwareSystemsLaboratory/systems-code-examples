#include "mutex.hh"
#include <pthread.h>
#include <stdio.h>

int count;
Mutex *lock = new Mutex();

void increment( int ntimes ) {
    for(int i = 0; i < ntimes; i++) {
        int c;
        lock->Lock();
        c = count;
        c = c+1;
        count = c;
        lock->Unlock();
    }
}

int main( int argc, char* argv[]) {
    const int n = 100000000;

    pthread_t thread1, thread2;
    pthread_attr_t threadAttribute;

    pthread_attr_init(&threadAttribute);
    pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %d\n", 2*n);

    pthread_create(&thread1, &threadAttribute, (void * (*)(void *))increment, (void *) n);
    pthread_create(&thread2, &threadAttribute, (void * (*)(void *))increment, (void *) n);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if( count != 2 * n ) {
        printf("****** Error. Final count is %d\n", count);
    } else {
        printf("****** OK. Final count is %d\n", count);
    }

    return 1;
}


