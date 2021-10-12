#include "cbuffer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cbuffer_new(cbuffer_t* buffer) {
    charlist_init(&buffer->charlist);
    buffer->pos = 0;
}

void cbuffer_add(cbuffer_t* buffer, char c) {
    struct charentry_t* my_entry = malloc(sizeof(struct charentry_t));\
    my_entry->c = c;
    TAILQ_INSERT_TAIL(buffer->charlist, my_entry, entries);
}
