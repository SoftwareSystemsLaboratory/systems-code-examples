#include "mutex.hh"
#include "queue.hh"
#include "semaphore.hh"
#include "debug.hh"
#include <pthread.h>
#include <stdio.h>

const int count_per_thread = 10000000;
int count;
Mutex *lock = new Mutex();
Semaphore *semaphore = new Semaphore(0);
Queue *queue = new Queue();

void increment()
{
    bool work_left = true;
    while(work_left)
    {
        lock->lock();
        if(!queue->has_work_left())
        {
            work_left = false;
        }
        else if(semaphore->down())
        {
            int work_item = queue->dequeue();
            count = count + work_item;
        }
        lock->unlock();
    }
}

void populate_queue()
{
    for(int i = 0; i < count_per_thread*2; i++)
    {
        lock->lock();
        queue->enqueue(1);
        semaphore->up();
        lock->unlock();
    }
    lock->lock();
    queue->done_adding();
    lock->unlock();
}

int main( int argc, char* argv[])
{

    pthread_t thread1, thread2;
    pthread_attr_t thread_attribute;

    pthread_attr_init(&thread_attribute);
    pthread_attr_setscope(&thread_attribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %d\n", 2*count_per_thread);

    pthread_create(&thread1, &thread_attribute, (void * (*)(void*))increment, (void*)NULL);
    pthread_create(&thread2, &thread_attribute, (void * (*)(void*))increment, (void*)NULL);

    populate_queue();

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if( count != 2 * count_per_thread )
    {
        printf("****** Error. Final count is %d\n", count);
    }
    else
    {
        printf("****** OK. Final count is %d\n", count);
    }

    return 1;
}
