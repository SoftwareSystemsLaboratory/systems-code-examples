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
 * - suppliers each generate options->gen_count values
 *   consumers consume only (options->gen_count * options->no_suppliers) / options->no_consumers entries
 *   some entries may NOT be consumed (ok under most circumstances)
 * - because consumers will stop after they have gotten their share of values, others are allowed to consume their fair share
 */

typedef struct
{
    bb_options_t* options;
    bounded_buffer_t* bb;
    int id;
} bb_tsd_t;

void* supplier(void *tsd)
{
    bb_tsd_t* bb_tsd = (bb_tsd_t*) tsd;
    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;
    int my_id = bb_tsd->id;

    lwlog_info("supplier { id: %d, state : \"running\", gen: %d }\n", my_id, options->gen_count);
    for (int i=0; i < options->gen_count; i++)
    {
        millisecond_sleep( rand() % options->supplier_max_delay_ms);
        entry_t* new_entry = (entry_t*) malloc(sizeof(entry_t));
        new_entry->value = my_id * options->gen_count + i;
        bounded_buffer_put(bb, new_entry);
        lwlog_info("supplier { id: %d,  entry: %d }\n", my_id, new_entry->value);
        bounded_buffer_print_info(bb);
    }
    lwlog_info("supplier { id: %d, state: \"exit\" }\n", my_id);
    pthread_exit(NULL);
}


/* note: consumer only consumesm options->no_suppliers * options->gen_count / options->no_consumers  entries (some may not be consumed, which is ok) */

void* consumer(void *tsd)
{
    bb_tsd_t* bb_tsd = (bb_tsd_t*) tsd;
    bounded_buffer_t* bb = bb_tsd->bb;
    bb_options_t* options = bb_tsd->options;
    int my_id = bb_tsd->id;
    int max_to_consume = options->no_suppliers * options->gen_count / options->no_consumers;
    int not_consumed = options->no_suppliers * options->gen_count % options->no_consumers;
    if (my_id < not_consumed)
        max_to_consume++;
    lwlog_info("consumer { id: %d, state: \"running\", messages: %d }\n", my_id, max_to_consume);
    for (int i=0; i < max_to_consume; i++)
    {
        entry_t* entry = bounded_buffer_get(bb);
        millisecond_sleep( rand() % options->consumer_max_delay_ms);
        lwlog_info("consumer { id: %d, entry: %d }\n", my_id, entry->value);
        bounded_buffer_print_info(bb);
        free(entry);
    }
    lwlog_info("consumer { id: %d, state: \"exit\" }\n", my_id);
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
    bb_tsd_t* bb_tsd = (bb_tsd_t*) malloc(no_threads * sizeof(bb_tsd_t));

    bb_options_print(&options);

    bounded_buffer_init(&bb, options.bsize);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* create supplier threads */
    for (int i=0; i < options.no_suppliers; i++)
    {
        int thread_number = i;
        bb_tsd[thread_number] = (bb_tsd_t)
        {
            .options = &options, .bb = &bb, .id = i
        };
        lwlog_info("pthread_create ( thread: %d, type: \"supplier\", id: %d }\n", thread_number, i);
        pthread_create(&threads[thread_number], &attr, supplier, (void *)&bb_tsd[thread_number]);
    }

    /* create supplier threads */
    for (int i=0; i < options.no_consumers; i++)
    {
        int thread_number = i+options.no_suppliers;
        bb_tsd[thread_number] = (bb_tsd_t)
        {
            .options = &options, .bb = &bb, .id = i
        };
        lwlog_info("pthread_create ( thread: %d, type: \"consumer\", id: %d }\n", thread_number, i);
        pthread_create(&threads[thread_number], &attr, consumer, (void *)&bb_tsd[thread_number]);
    }

    lwlog_info("main { threads:  %d, state: \"started\" }\n", no_threads);

    for (int i=0; i < no_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    lwlog_info("main { threads:  %d,  state: \"joined\" }\n", no_threads);

    lwlog_info("main { extra_entires:  %d }\n", bounded_buffer_count(&bb));

    int bb_size = bounded_buffer_count(&bb);
    for (int i=0; i < bb_size; i++)
    {
        entry_t* e = bounded_buffer_get(&bb);
        lwlog_info("main { removed: %d }\n", e->value);
        free(e);
    }
    pthread_attr_destroy(&attr);
    bounded_buffer_cleanup(&bb);
    free(threads);
    free(bb_tsd);

    pthread_exit(NULL);
}

