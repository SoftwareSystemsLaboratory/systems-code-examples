#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT 12

/* this version eliminates global variable declarations and uses thread-specific data with
 * a pointer to any data that is shared but under mutex control
 */

typedef struct
{
    int count;
    pthread_mutex_t count_mutex;
    pthread_cond_t count_threshold_cv;
} shared_data_t;

typedef struct
{
    int my_id;
    shared_data_t* common; /* the mutex, cv, and count are all kept in a common structure */
} tsd_t;

void *inc_count(void *t)
{
    tsd_t* tsd = (tsd_t*) t;
    long my_id = tsd->my_id;
    int i;

    for (i=0; i<TCOUNT; i++)
    {
        pthread_mutex_lock(&tsd->common->count_mutex);
        tsd->common->count++;

        /*
        Check the value of count and signal waiting thread when condition is
        reached.  Note that this occurs while mutex is locked.
        */
        if (tsd->common->count == COUNT_LIMIT)
        {
            pthread_cond_signal(&tsd->common->count_threshold_cv);
            printf("inc_count(): thread %ld, count = %d  Threshold reached.\n",
                   my_id, tsd->common->count);
        }
        printf("inc_count(): thread %ld, count = %d, i = %d, unlocking mutex\n",
               my_id, tsd->common->count, i);
        pthread_mutex_unlock(&tsd->common->count_mutex);

        /* Do some "work" so threads can alternate on mutex lock */
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watch_count(void *t)
{
    tsd_t* tsd = (tsd_t*) t;
    long my_id = tsd->my_id;

    printf("Starting watch_count(): thread %ld\n", my_id);

    /*
    Lock mutex and wait for signal.  Note that the pthread_cond_wait
    routine will automatically and atomically unlock mutex while it waits.
    Also, note that if COUNT_LIMIT is reached before this routine is run by
    the waiting thread, the loop will be skipped to prevent pthread_cond_wait
    from never returning.
    */
    pthread_mutex_lock(&tsd->common->count_mutex);
    while (tsd->common->count<COUNT_LIMIT)
    {
        pthread_cond_wait(&tsd->common->count_threshold_cv, &tsd->common->count_mutex);
        printf("watch_count(): thread %ld Condition signal received.\n", my_id);
    }
    tsd->common->count += 125;
    printf("watch_count(): thread %ld count now = %d.\n", my_id, tsd->common->count);
    pthread_mutex_unlock(&tsd->common->count_mutex);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    int i, rc;

    shared_data_t shared_data;
    tsd_t tsd[NUM_THREADS];


    pthread_t threads[3];
    pthread_attr_t attr;

    /* Initialize mutex and condition variable objects */
    shared_data.count = 0;
    pthread_mutex_init(&shared_data.count_mutex, NULL);
    pthread_cond_init (&shared_data.count_threshold_cv, NULL);

    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (int i=0; i < NUM_THREADS; i++)
    {
        tsd[i].my_id = i+1;
        tsd[i].common = &shared_data;
    }

    pthread_create(&threads[0], &attr, watch_count, (void *)&tsd[0]);
    pthread_create(&threads[1], &attr, inc_count, (void *)&tsd[1]);
    pthread_create(&threads[2], &attr, inc_count, (void *)&tsd[2]);

    /* Wait for all threads to complete */
    for (i=0; i<NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);

    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&shared_data.count_mutex);
    pthread_cond_destroy(&shared_data.count_threshold_cv);
    pthread_exit(NULL);

}

