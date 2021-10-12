#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#ifndef CHARLIST_TAILQ_H
#define CHARLIST_TAILQ_H

TAILQ_HEAD(charlist_t, charentry_t);

struct charentry_t {
  char c;
  TAILQ_ENTRY(charentry_t) entries;
};

extern void charlist_add(struct charlist_t* head_ptr, char char);

extern void charlist_print(struct charlist_t* head_ptr);

extern void charlist_delete(struct charlist_t* head_ptr);

extern void charlist_init(struct charlist_t* head_ptr);

#endif
