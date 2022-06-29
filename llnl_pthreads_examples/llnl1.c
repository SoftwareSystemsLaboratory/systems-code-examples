/* adapted from LLNL pthreads tutorial
 * https://computing.llnl.gov/tutorials/pthreads
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS     5

struct thread_data
{
    long tid;
    long square;
};

typedef struct thread_data thread_data_t;



void *PrintHello(void *td_ptr)
{
    thread_data_t *td = (thread_data_t *)td_ptr;
    printf("Hello World! It's me, thread #%ld!\n", td->tid);
    printf("sqr(%ld) = %ld\n", td->tid, td->square);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++)
    {
        thread_data[t].tid = t;
        thread_data[t].square = t * t;
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, &thread_data[t]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    printf("Exiting main thread\n");
    pthread_exit(NULL);
}
