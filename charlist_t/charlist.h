#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#ifndef CHARLIST_TAILQ_H
#define CHARLIST_TAILQ_H

TAILQ_HEAD(charlist_t, charentry_t);

struct charentry_t
{
    char c;
    TAILQ_ENTRY(charentry_t) entries;
};

extern void charlist_add_char(struct charlist_t* head_ptr, char c);

extern void charlist_add_string(struct charlist_t* head_ptr, char* text);

extern void charlist_print(struct charlist_t* head_ptr);

extern void charlist_delete(struct charlist_t* head_ptr);

extern void charlist_init(struct charlist_t* head_ptr);

extern int charlist_size_slow(struct charlist_t* head_ptr);

extern char* charlist_tostring(struct charlist_t* head_ptr);

typedef struct charlist_t charlist_t;

#endif
