#include <pthread.h>
#include <stdio.h>

#include "diners.h"
#include "millisleep.h"


int main(int argc, char *argv[]) {

    fork_t fork[MAX_DINERS];
    diner_t diner[MAX_DINERS];
    pthread_t diner_thread[MAX_DINERS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t this_thread = pthread_self();
    struct sched_param sched_parameters;
    sched_parameters.sched_priority = sched_get_priority_max(SCHED_OTHER);
    int status = pthread_setschedparam(this_thread, SCHED_OTHER, &sched_parameters);


    if (get_dining_policy() == FORK_REORDERING)
        printf("Enumerating forks to avoid deadlock.");
    else
        printf("Not Enumerating forks to avoid deadlock.");

    if (status != 0) {
        fprintf(stderr, "Cannot set max prioirty.\n");
        //exit(1);
    }

    int go_on = 1;

    for (int i = 0; i < MAX_DINERS; i++)
        fork_init(&fork[i], i);

    for (int i = 0; i < MAX_DINERS; i++) {
        if (get_dining_policy() == FORK_REORDERING) {
            int id1 = i;
            int id2 = (i + 1) % MAX_DINERS;
            if (id1 < id2)
                diner_init(&diner[i], &fork[id1], &fork[id2]);
            else {
                printf("Reordered forks %d and %d\n", id1, id2);
                diner_init(&diner[i], &fork[id2], &fork[id1]);
            }
        } else
            diner_init(&diner[i], &fork[i], &fork[(i + 1) % MAX_DINERS]);
    }

    for (int i = 0; i < MAX_DINERS; i++) {
        printf("Creating thread %d", i);
        pthread_create(&diner_thread[i], &attr, diner_run, (void *) &diner[i]);
    }

    // set current (main) thread to max priority
    //
    //
    while (go_on) {
        for (int i = 0; i < MAX_DINERS; i++) {
            putchar(diner[i].state);
        }
        putchar('\n');
        go_on = 0;
        for (int i = 0; i < MAX_DINERS; i++) {
            go_on |= diner[i].state != 'd';
        }
        millisecond_sleep(MAIN_THREAD_SLEEP_TIME);
    }
}
