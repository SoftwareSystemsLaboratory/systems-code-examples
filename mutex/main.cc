#include "mutex.hh"
#include <pthread.h>
#include <stdio.h>

int count;
Mutex *lock = new Mutex();

void increment( int iterations )
{
    for(int i = 0; i < iterations; i++)
    {
        int local_count;
        lock->lock();
        local_count = count;
        local_count = local_count + 1;
        count = local_count;
        lock->unlock();
    }
}

int main( int argc, char* argv[])
{
    const int iterations = 100000000;

    pthread_t thread1, thread2;
    pthread_attr_t thread_attribute;

    pthread_attr_init(&thread_attribute);
    pthread_attr_setscope(&thread_attribute, PTHREAD_SCOPE_SYSTEM);

    printf("starting test. final count should be %d\n", 2*iterations);

    pthread_create(&thread1, &thread_attribute, (void * (*)(void *))increment, (void *) iterations);
    pthread_create(&thread2, &thread_attribute, (void * (*)(void *))increment, (void *) iterations);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if( count != 2 * iterations )
    {
        printf("****** Error. Final count is %d\n", count);
    }
    else
    {
        printf("****** OK. Final count is %d\n", count);
    }

    return 1;
}
