#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "diners.h"
#include "millisleep.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_DINERS 5
#define MAX_THINK_TIME 7
#define MAX_EAT_TIME 7
#define MAIN_THREAD_SLEEP_TIME 51

typedef struct {
    int num_philosophers;
    int think_time;
    int eat_time;
    int enumerate_resources;
} Configuration;

void parseCommandLine(int argc, char **argv, Configuration *config) {
    int opt;

    while ((opt = getopt(argc, argv, "n:t:e:r")) != -1) {
        switch (opt) {
            case 'n': // Number of philosophers
                config->num_philosophers = atoi(optarg);
                if (config->num_philosophers > MAX_DINERS || config->num_philosophers < 1) {
                    fprintf(stderr, "Number of philosophers must be between 1 and %d\n", MAX_DINERS);
                    exit(EXIT_FAILURE);
                }
                break;
            case 't': // Think time
                config->think_time = atoi(optarg);
                if (config->think_time > MAX_THINK_TIME || config->think_time < 0) {
                    fprintf(stderr, "Think time must be between 0 and %d seconds\n", MAX_THINK_TIME);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'e': // Eat time
                config->eat_time = atoi(optarg);
                if (config->eat_time > MAX_EAT_TIME || config->eat_time < 0) {
                    fprintf(stderr, "Eat time must be between 0 and %d seconds\n", MAX_EAT_TIME);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'r': // Enumerate resources
                config->enumerate_resources = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-n num_philosophers] [-t think_time] [-e eat_time] [-r]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char **argv) {
    Configuration config = {
        .num_philosophers = 5,      // default number of philosophers
        .think_time = 2,            // default think time in seconds
        .eat_time = 3,              // default eat time in seconds
        .enumerate_resources = 0    // default for resource enumeration: off
    };

    parseCommandLine(argc, argv, &config);

    printf("Number of Philosophers: %d\n", config.num_philosophers);
    printf("Think Time: %d seconds\n", config.think_time);
    printf("Eat Time: %d seconds\n", config.eat_time);
    printf("Enumerate Resources: %s\n", config.enumerate_resources ? "Yes" : "No");

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

    if (status != 0)
    {
        fprintf(stderr, "Cannot set main thread max prioirty. Fatal.\n");
        exit(1);
    }

    /* initialize the shared resources (forks) */
    for (int i = 0; i < MAX_DINERS; i++)
        fork_init(&fork[i], i);

    /* initialize the diners to link to the shared resources (forks) */
    for (int i = 0; i < MAX_DINERS; i++)
    {
        int id1 = i;
        int id2 = (i + 1) % MAX_DINERS;
        if (get_dining_policy() == FORK_REORDERING && id1 > id2)
        {
            printf("Reordered forks %d and %d\n", id1, id2);
            diner_init(&diner[i], i, &fork[id2], &fork[id1]);
        }
        else
        {
            diner_init(&diner[i], i, &fork[id1], &fork[id2]);
        }
    }

    /* start the actual threads for each diner */
    for (int i = 0; i < MAX_DINERS; i++)
    {
        printf("Creating thread %d", i);
        diner_start(&diner[i]);
    }

    /* monitor the state of the diners in the main (highest-priority) thread
     * because it is high priority, it must sleep for a short time to give
     * the diner threads a chance to do their thing.
     */
    int go_on = 1;
    while (go_on)
    {
        for (int i = 0; i < MAX_DINERS; i++)
        {
            putchar(diner[i].state);
        }
        putchar('\n');
        go_on = 0;
        for (int i = 0; i < MAX_DINERS; i++)
        {
            go_on |= diner[i].state != 'd';
        }
        millisecond_sleep(MAIN_THREAD_SLEEP_TIME);
    }

    /* assuming no deadlock happened, this code will be reached so we
     * can join with the main thread
     */

    for (int i=0; i < MAX_DINERS; i++)
    {
        diner_await(&diner[i]);
        printf("Diner id %c exited normally; state = %c\n", diner[i].id, diner[i].state);
    }

    /* locks associated with forks need to be cleaned up */
    for (int i = 0; i < MAX_DINERS; i++)
        fork_free_resources(&fork[i]);

    /* attribute object should also be freed (could do earlier, too) */
    //pthread_attr_destroy(&attr);
}
