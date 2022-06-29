#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#ifndef WORDLIST_TAILQ_H
#define WORDLIST_TAILQ_H

TAILQ_HEAD(wordlist_t, wordentry_t);

struct wordentry_t
{
    char* text;
    TAILQ_ENTRY(wordentry_t) entries;
};

extern void wordlist_add(struct wordlist_t* head_ptr, char* word);

extern void wordlist_print(struct wordlist_t* head_ptr);

extern void wordlist_delete(struct wordlist_t* head_ptr);

extern void wordlist_init(struct wordlist_t* head_ptr);

#endif
