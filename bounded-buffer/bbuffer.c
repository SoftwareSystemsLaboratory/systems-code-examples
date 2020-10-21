#include "bbuffer.h"

#include <stdlib.h>

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
