#include "mutex.hh"
#include "queue.hh"
#include "semaphore.hh"
#include "debug.hh"
#include <pthread.h>
#include <stdio.h>

const int countPerThread = 10000000;
int count;
Mutex *lock = new Mutex();
Semaphore *semaphore = new Semaphore(0);
Queue *queue = new Queue();

void increment() {
    bool workLeft = true;
    while(workLeft) {
        lock->Lock();
        if(!queue->HasWorkLeft()) {
            workLeft = false;
        } else if(semaphore->Down()) {
            int c = queue->Dequeue();
            count = count + c;
        }
        lock->Unlock();
    }
}

void populateQueue() {
    for(int i = 0; i < countPerThread*2; i++) {
        lock->Lock();
        queue->Enqueue(1);
        semaphore->Up();
        lock->Unlock();
    }
    lock->Lock();
    queue->DoneAdding();
    lock->Unlock();
}

int main( int argc, char* argv[]) {

    pthread_t thread1, thread2;
    pthread_attr_t threadAttribute;

    pthread_attr_init(&threadAttribute);
    pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %d\n", 2*countPerThread);

    pthread_create(&thread1, &threadAttribute, (void * (*)(void*))increment, (void*)NULL);
    pthread_create(&thread2, &threadAttribute, (void * (*)(void*))increment, (void*)NULL);

    populateQueue();

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if( count != 2 * countPerThread ) {
        printf("****** Error. Final count is %d\n", count);
    } else {
        printf("****** OK. Final count is %d\n", count);
    }

    return 1;
}


