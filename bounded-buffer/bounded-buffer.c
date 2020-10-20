#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "bboptions.h"
#include "bbuffer.h"

#include "millisleep.h"

#define DEBUG(fmt, ...) do { fprintf(stderr, fmt, ## __VA_ARGS__); } while (0)

#define INFO(fmt, ...) do { fprintf(stdout, fmt, ## __VA_ARGS__); } while (0)

typedef struct {
    bb_options_t* options;
    bounded_buffer_t* bb;
    int id;
} bb_thread_specific_data_t;

/* note: supplier generates options->gen_count entries */

void* supplier(void *tsd)
{
    bb_thread_specific_data_t* bb_tsd = (bb_thread_specific_data_t*) tsd;

    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;
    int my_id = bb_tsd->id;

    DEBUG("Starting supplier(): will supply %d messages\n", options->gen_count);
    for (int i=0; i < options->gen_count; i++) {
        millisecond_sleep( rand() % options->supplier_max_delay_ms);
        entry_t* new_entry = (entry_t*) malloc(sizeof(entry_t));
        new_entry->value = my_id * options->gen_count + i;
        DEBUG("producer %d added entry %d\n", my_id, new_entry->value);
        bounded_buffer_put(bb, new_entry);
        INFO("buffer size est = %d\n", bb->tail - bb->head);
    }
    INFO("supplier %d is done\n", my_id);
    pthread_exit(NULL);
}


/* note: consumer only consumesm options->no_suppliers * options->gen_count / options->no_consumers  entries (some may not be consumed, which is ok) */

void* consumer(void *tsd)
{
    bb_thread_specific_data_t* bb_tsd = (bb_thread_specific_data_t*) tsd;

    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;
    int my_id = bb_tsd->id;
    int max_to_consume = options->no_suppliers * options->gen_count / options->no_consumers;
    DEBUG("Starting consumer(): will consume %d messages \n", max_to_consume);
    int not_consumed = options->no_suppliers * options->gen_count % options->no_consumers;
    if (not_consumed > 0)
        DEBUG("Note: %d messages will be left in buffer at the end\n", not_consumed);
    for (int i=0; i < max_to_consume; i++) {
        entry_t* entry = bounded_buffer_get(bb);
        INFO("buffer size est = %d\n", bb->tail - bb->head);
        millisecond_sleep( rand() % options->consumer_max_delay_ms);
        DEBUG("consumer %d got entry %d\n", my_id, entry->value);
        free(entry);
    }
    INFO("consumer %d is done\n", my_id);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_attr_t attr;
    bounded_buffer_t bb;
    bb_options_t options;


    bb_options_get(&options, argc, argv);
    int no_threads = options.no_suppliers + options.no_consumers;
    pthread_t* threads = (pthread_t*) malloc(no_threads * sizeof(pthread_t));
    bb_thread_specific_data_t* bb_tsd = (bb_thread_specific_data_t*) malloc(no_threads * sizeof(bb_thread_specific_data_t));

    bb_options_print(&options);

    bounded_buffer_init(&bb, options.bsize);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* TODO: Consider making thread-specific data include supplier/consumer IDs */
    int thread_count = 0;
    bb_thread_specific_data_t common_tsd = { &options, &bb, -1 };
    for (int i=0; i < options.no_suppliers; i++) {
        bb_tsd[thread_count] = common_tsd;
        bb_tsd[thread_count].id = i;
        pthread_create(&threads[thread_count], &attr, supplier, (void *)&bb_tsd[thread_count]);
        thread_count++;
    }
    DEBUG("producer threads created total = %d\n", thread_count);

    for (int i=0; i < options.no_consumers; i++) {
        bb_tsd[thread_count] = common_tsd;
        bb_tsd[thread_count].id = i;
        pthread_create(&threads[thread_count], &attr, consumer, (void *)&bb_tsd[thread_count]);
        thread_count++;
    }
    DEBUG("threads created total = %d\n", thread_count);

    for (int i=0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    DEBUG("joined with producer and consumer threads\n");

    pthread_attr_destroy(&attr);
    free(threads);

    DEBUG("freed all pthread_t resources\n");

    pthread_exit(NULL);
}

