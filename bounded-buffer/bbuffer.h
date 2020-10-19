#ifndef _BBUFFER_H_
#define _BBUFFER_H_

#include <pthread.h>

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

extern void bounded_buffer_init(bounded_buffer_t* bb, int size);
extern void bounded_buffer_put(bounded_buffer_t* bb, entry_t* item);
extern entry_t* bounded_buffer_get(bounded_buffer_t* bb);

#endif
