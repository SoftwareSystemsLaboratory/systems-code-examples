#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* TODO: add getopt() support soon */

#define BB_SIZE 100
#define GEN_COUNT 2000

/* we should be able to support any number of suppliers and consumers */

#define NUM_SUPPLIERS 1
#define NUM_CONSUMERS 1
#define NUM_THREADS ((NUM_SUPPLIERS) + (NUM_CONSUMERS))

#define SUPPLIER_DELAY 300
#define CONSUMER_DELAY 1000

#include "millisleep.h"

typedef struct {
    int value;
} entry_t;

typedef struct {
    int size;
    entry_t** entries;
    int head;
    int tail;
    pthread_mutex_t lock;
    pthread_cond_t has_space;
    pthread_cond_t has_items;
} bounded_buffer_t;

void bounded_buffer_init(bounded_buffer_t* bb, int size) {
    bb->entries = (entry_t**) malloc(size * sizeof(entry_t*));
    for (int i=0; i < size; i++)
        bb->entries[size] = NULL;
    bb->size = size;
    bb->head = bb->tail = 0;
    pthread_mutex_init(&bb->lock, NULL);
    pthread_cond_init (&bb->has_space, NULL);
    pthread_cond_init (&bb->has_items, NULL);
}

void bounded_buffer_put(bounded_buffer_t* bb, entry_t* item)  {
    pthread_mutex_lock(&bb->lock);

    while (bb->tail - bb->head >= bb->size) {
        pthread_cond_wait(&bb->has_space, &bb->lock);
    }

    bb->entries[bb->tail++ % bb->size] = item;
    pthread_cond_signal(&bb->has_items);

    pthread_mutex_unlock(&bb->lock);
}

entry_t* bounded_buffer_get(bounded_buffer_t* bb)  {
    pthread_mutex_lock(&bb->lock);

    while (bb->tail == bb->head) {
        pthread_cond_wait(&bb->has_items, &bb->lock);
    }

    entry_t* entry = bb->entries[bb->head % bb->size];
    bb->entries[bb->head++ % bb->size] = NULL;
    pthread_cond_signal(&bb->has_space);

    pthread_mutex_unlock(&bb->lock);
    return entry;
}

void bounded_buffer_cleanup(bounded_buffer_t* bb) {
    pthread_mutex_destroy(&bb->lock);
    pthread_cond_destroy(&bb->has_space);
    pthread_cond_destroy(&bb->has_items);
}

/* suppliers will produce NUM_SUPPLIERS * GEN_COUNT messages */

void* supplier(void *tsd)
{
    bounded_buffer_t* bb = (bounded_buffer_t*) tsd;
    printf("Starting supplier(): will supply %d messages\n", GEN_COUNT);
    for (int i=0; i < GEN_COUNT; i++) {
        millisecond_sleep( rand() % SUPPLIER_DELAY);
        entry_t* new_entry = (entry_t*) malloc(sizeof(entry_t));
        new_entry->value = i;
        bounded_buffer_put(bb, new_entry);
        printf("buffer size est = %d\n", bb->tail - bb->head);
    }
    pthread_exit(NULL);
}

/* consumers will consume NUM_SUPPLIERS * GEN_COUNT / NUM_CONSUMERS messages each */

void* consumer(void *tsd)
{
    bounded_buffer_t* bb = (bounded_buffer_t*) tsd;
    int max_to_consume = NUM_SUPPLIERS * GEN_COUNT / NUM_CONSUMERS;
    printf("Starting consumer(): will consume %d messages \n", max_to_consume);
    int not_consumed = NUM_SUPPLIERS * GEN_COUNT % NUM_CONSUMERS;
    if (not_consumed > 0)
      printf("Note: %d messages will be left in buffer at the end\n", not_consumed);
    for (int i=0; i < max_to_consume; i++) {
        entry_t* entry = bounded_buffer_get(bb);
        printf("buffer size est = %d\n", bb->tail - bb->head);
        millisecond_sleep( rand() % CONSUMER_DELAY);
        printf("got entry %d\n", entry->value);
        free(entry);
    }
    pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    bounded_buffer_t bb;
    bounded_buffer_init(&bb, BB_SIZE);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* TODO: Consider making thread-specific data include supplier/consumer IDs */
    int thread_count = 0;
    for (int i=0; i < NUM_SUPPLIERS; i++)
        pthread_create(&threads[thread_count++], &attr, supplier, (void *)&bb);

    for (int i=0; i < NUM_CONSUMERS; i++)
        pthread_create(&threads[thread_count++], &attr, consumer, (void *)&bb);

    for (int i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf ("joined with producer and consumer threads");

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}

