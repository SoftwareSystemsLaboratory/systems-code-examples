#include "trans.hh"
#include <pthread.h>
#include <stdio.h>

const int count_per_thread = 10000000;
volatile int count = 0;
Transaction *trans = new Transaction(&count);

void increment()
{
    const int chunk_size = 500;
    for(int i = 0; i < count_per_thread; i += chunk_size)
    {
        MemHandle* handle;
        do
        {
            handle = trans->begin();
            for(int j = 0; j < chunk_size; j++)
            {
                handle->value += 1;
            }
        }
        while(!trans->try_commit(handle));
    }
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

    printf("rollback count = %d\n", trans->get_rollback_count());

    return 1;
}

