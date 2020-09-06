#include "queue.hh"
#include "monitor.hh"
#include "debug.hh"
#include <pthread.h>
#include <stdio.h>

const int countPerThread = 10000000;
int count;
Monitor *monitor = new Monitor();
Queue *queue = new Queue();

void increment() {
    monitor->Enter();
    while(queue->HasWorkLeft()) {
        while(queue->IsEmpty() && queue->HasWorkLeft()) {
            monitor->Wait();
        }
        if(!queue->IsEmpty()) {
            int c = queue->Dequeue();
            count = count + c;
        }
    }
    monitor->Exit();
}

void populateQueue() {
    for(int i = 0; i < countPerThread*2; i++) {
        monitor->Enter();
        queue->Enqueue(1);
        monitor->Pulse();
        monitor->Exit();
    }
    monitor->Enter();
    queue->DoneAdding();
    monitor->Exit();
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


