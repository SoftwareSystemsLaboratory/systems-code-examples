#include "queue.hh"
#include "monitor.hh"
#include "debug.hh"
#include <pthread.h>
#include <stdio.h>

const int count_per_thread = 10000000;
int count;
Monitor *monitor = new Monitor();
Queue *queue = new Queue();

void increment()
{
    monitor->enter();
    while(queue->has_work_left())
    {
        while(queue->is_empty() && queue->has_work_left())
        {
            monitor->wait();
        }
        if(!queue->is_empty())
        {
            int work_item = queue->dequeue();
            count = count + work_item;
        }
    }
    monitor->exit();
}

void populate_queue()
{
    for(int i = 0; i < count_per_thread*2; i++)
    {
        monitor->enter();
        queue->enqueue(1);
        monitor->pulse();
        monitor->exit();
    }
    monitor->enter();
    queue->done_adding();
    monitor->exit();
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
