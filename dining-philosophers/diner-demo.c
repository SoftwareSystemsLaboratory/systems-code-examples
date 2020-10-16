#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "diners.h"
#include "millisleep.h"


int main(int argc, char *argv[]) {

    fork_t fork[MAX_DINERS];
    diner_t diner[MAX_DINERS];

    /* The main thread  */
    pthread_t this_thread = pthread_self();
    struct sched_param sched_parameters;
    sched_parameters.sched_priority = sched_get_priority_max(SCHED_OTHER);
    int status = pthread_setschedparam(this_thread, SCHED_OTHER, &sched_parameters);

    // the main thread monitors the state of the diners and runs at highest
    // priority so it can continue doing something, even if (or when) the other
    // threads get deadlocked.

    if (status != 0) {
        fprintf(stderr, "Cannot set main thread max prioirty. Fatal.\n");
        exit(1);
    }

    /* initialize the shared resources (forks) */
    for (int i = 0; i < MAX_DINERS; i++)
        fork_init(&fork[i], i);

    /* initialize the diners to link to the shared resources (forks) */
    for (int i = 0; i < MAX_DINERS; i++) {
        int id1 = i;
        int id2 = (i + 1) % MAX_DINERS;
        if (get_dining_policy() == FORK_REORDERING && id1 > id2) {
            printf("Reordered forks %d and %d\n", id1, id2);
            diner_init(&diner[i], i, &fork[id2], &fork[id1]);
        } else {
            diner_init(&diner[i], i, &fork[id1], &fork[id2]);
        }
    }

    /* start the actual threads for each diner */
    for (int i = 0; i < MAX_DINERS; i++) {
        printf("Creating thread %d", i);
        diner_start(&diner[i]);
    }

    /* monitor the state of the diners in the main (highest-priority) thread
     * because it is high priority, it must sleep for a short time to give
     * the diner threads a chance to do their thing.
     */
    int go_on = 1;
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

    /* assuming no deadlock happened, this code will be reached so we
     * can join with the main thread
     */

    for (int i=0; i < MAX_DINERS; i++) {
        diner_await(&diner[i]);
        printf("Diner id %c exited normally; state = %c\n", diner[i].id, diner[i].state);
    }

    /* locks associated with forks need to be cleaned up */
    for (int i = 0; i < MAX_DINERS; i++)
        fork_free_resources(&fork[i]);

    /* attribute object should also be freed (could do earlier, too) */
    //pthread_attr_destroy(&attr);
}
