#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "bboptions.h"
#include "bbuffer.h"

#include "millisleep.h"



/*
 * bounded buffer example where there can be any number of suppliers and consumers
 *
 * in this design:
 * - each supplier and consumer runs as a separate thread
 *   thread-specific data allows each to share the bound_buffer_t* instance and command-line options/config
 *   each supplier and consumer knows its own id.
 * - suppliers each produce options->gen_count values
 *   consumers consume only (options->gen_count * options->no_suppliers) / options->no_consumers entries
 *   some entries may NOT be consumed (ok under most circumstances)
 * - because consumers will stop after they have gotten their share of values, others are allowed to consume their fair share
 */

typedef struct {
    bb_options_t* options;
    bounded_buffer_t* bb;
    int id;
} bb_thread_specific_data_t;

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
        bounded_buffer_put(bb, new_entry);
        INFO("producer %d added entry %d [buffer size = %d, head %d tail %d]\n", my_id, new_entry->value, bounded_buffer_size(bb), bb->head, bb->tail);
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
        millisecond_sleep( rand() % options->consumer_max_delay_ms);
        INFO("consumer %d got entry %d [buffer size = %d head %d tail %d]\n", my_id, entry->value, bounded_buffer_size(bb), bb->head, bb->tail);
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

    int thread_count = 0;
    for (int i=0; i < options.no_suppliers; i++) {
        // This is called a compound literal, which allows you to initialize fields of a struct in a statement.
        bb_tsd[thread_count] = (bb_thread_specific_data_t) { .options = &options, .bb = &bb, .id = i };
        pthread_create(&threads[thread_count], &attr, supplier, (void *)&bb_tsd[thread_count]);
        thread_count++;
    }
    for (int i=0; i < options.no_consumers; i++) {
        bb_tsd[thread_count] = (bb_thread_specific_data_t) { .options = &options, .bb = &bb, .id = i };
        pthread_create(&threads[thread_count], &attr, consumer, (void *)&bb_tsd[thread_count]);
        thread_count++;
    }
    DEBUG("threads created = %d\n", thread_count);

    for (int i=0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    DEBUG("joined with producer and consumer threads\n");

    pthread_attr_destroy(&attr);
    bounded_buffer_cleanup(&bb);
    free(threads);
    free(bb_tsd);

    DEBUG("freed all pthread_t resources\n");

    pthread_exit(NULL);
}

