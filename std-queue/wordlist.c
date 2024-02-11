#include <stdio.h>
#include <stdlib.h>

#include "wordlist.h"

void wordlist_add(struct wordlist_t *head_ptr, char *word) {
    struct wordentry_t *my_entry = malloc(sizeof(struct wordentry_t));
    my_entry->text = word;
    TAILQ_INSERT_TAIL(head_ptr, my_entry, entries);
}

void wordlist_print(struct wordlist_t *head_ptr) {
    struct wordentry_t *np;
    TAILQ_FOREACH(np, head_ptr, entries) {
        printf("%s\n", np->text);
    }
}

void wordlist_delete(struct wordlist_t *head_ptr) {
    struct wordentry_t *n1, *n2;
    n1 = TAILQ_FIRST(head_ptr);
    while (n1 != NULL) {
        n2 = TAILQ_NEXT(n1, entries);
        free(n1);
        n1 = n2;
    }
}

void wordlist_init(struct wordlist_t *head_ptr) {
    struct wordlist_t head = TAILQ_HEAD_INITIALIZER(head);
    *head_ptr = head;
    /* create a tail queue */
    TAILQ_INIT(head_ptr);
}

