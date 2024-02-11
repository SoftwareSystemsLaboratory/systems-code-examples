#include "strbuffer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strbuffer_new(strbuffer_t *buffer) {
    strbuffer_init(buffer, MIN_CAPACITY, MIN_INCREMENT);
}

void strbuffer_init(strbuffer_t *buffer, int capacity, int increment) {
    if (capacity < MIN_CAPACITY)
        buffer->capacity = MIN_CAPACITY;
    else buffer->capacity = capacity;

    if (increment < MIN_INCREMENT)
        buffer->increment = MIN_INCREMENT;
    else buffer->increment = increment;

    buffer->data = (char *) malloc(buffer->capacity * sizeof(char));
    buffer->pos = 0;
}


void strbuffer_resize_if_needed(strbuffer_t *buffer) {
    if (buffer->pos < buffer->capacity)
        return;

    int new_capacity = buffer->capacity + buffer->increment;
    //printf("Resizing to %d\n", new_capacity);
    buffer->data = (char *) realloc(buffer->data, new_capacity * sizeof(char));
    buffer->capacity = new_capacity;
}

void strbuffer_append(strbuffer_t *buffer, char c) {
    strbuffer_resize_if_needed(buffer);
    buffer->data[buffer->pos++] = c;
}

char *strbuffer_tostring(strbuffer_t *buffer) {
    char *repr = (char *) malloc((buffer->pos + 1) * sizeof(char));
    memcpy(repr, buffer->data, buffer->pos * sizeof(char));
    repr[buffer->pos] = 0;
    return repr;
}

void strbuffer_reset(strbuffer_t *buffer) {
    buffer->pos = 0;
}


char *strbuffer_getline(strbuffer_t *buffer, int *eof) {
    int c;
    *eof = 0;
    strbuffer_reset(buffer);
    for (;;) {
        c = getchar();
        if (c == '\n' || c == '\r' || c == 0 || c == EOF)
            break;
        strbuffer_append(buffer, c);
    }
    if (c == EOF) *eof = 1;
    return strbuffer_tostring(buffer);
}

