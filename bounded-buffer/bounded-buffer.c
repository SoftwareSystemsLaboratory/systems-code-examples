#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "bboptions.h"
#include "bbuffer.h"

#define NUM_THREADS ((NUM_SUPPLIERS) + (NUM_CONSUMERS))

#include "millisleep.h"

/* suppliers will produce NUM_SUPPLIERS * GEN_COUNT messages */

/* Threads need to know the options & the pointer to the common bounded buffer */


#define DEBUG(fmt, ...) do { fprintf(stderr, fmt, ## __VA_ARGS__); } while (0)

#define INFO(fmt, ...) do { fprintf(stdout, fmt, ## __VA_ARGS__); } while (0)

typedef struct {
    bb_options_t* options;
    bounded_buffer_t* bb;
} bb_thread_specific_data_t;

void* supplier(void *tsd)
{
    bb_thread_specific_data_t* bb_tsd = (bb_thread_specific_data_t*) tsd;

    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;

    DEBUG("Starting supplier(): will supply %d messages\n", GEN_COUNT);
    for (int i=0; i < GEN_COUNT; i++) {
        millisecond_sleep( rand() % SUPPLIER_DELAY);
        entry_t* new_entry = (entry_t*) malloc(sizeof(entry_t));
        new_entry->value = i;
        bounded_buffer_put(bb, new_entry);
        INFO("buffer size est = %d\n", bb->tail - bb->head);
    }
    pthread_exit(NULL);
}

/* consumers will consume NUM_SUPPLIERS * GEN_COUNT / NUM_CONSUMERS messages each */

void* consumer(void *tsd)
{
    bb_thread_specific_data_t* bb_tsd = (bb_thread_specific_data_t*) tsd;

    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;
    int max_to_consume = NUM_SUPPLIERS * GEN_COUNT / NUM_CONSUMERS;
    DEBUG("Starting consumer(): will consume %d messages \n", max_to_consume);
    int not_consumed = NUM_SUPPLIERS * GEN_COUNT % NUM_CONSUMERS;
    if (not_consumed > 0)
        DEBUG("Note: %d messages will be left in buffer at the end\n", not_consumed);
    for (int i=0; i < max_to_consume; i++) {
        entry_t* entry = bounded_buffer_get(bb);
        INFO("buffer size est = %d\n", bb->tail - bb->head);
        millisecond_sleep( rand() % CONSUMER_DELAY);
        DEBUG("got entry %d\n", entry->value);
        free(entry);
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    bounded_buffer_t bb;
    bb_options_t options;

    bb_thread_specific_data_t bb_tsd = { &options, &bb };

    bb_options_get(&options, argc, argv);
    bb_options_print(&options);

    bounded_buffer_init(&bb, BB_SIZE);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* TODO: Consider making thread-specific data include supplier/consumer IDs */
    int thread_count = 0;
    for (int i=0; i < NUM_SUPPLIERS; i++)
        pthread_create(&threads[thread_count++], &attr, supplier, (void *)&bb_tsd);

    for (int i=0; i < NUM_CONSUMERS; i++)
        pthread_create(&threads[thread_count++], &attr, consumer, (void *)&bb_tsd);

    for (int i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    DEBUG("joined with producer and consumer threads");

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}

