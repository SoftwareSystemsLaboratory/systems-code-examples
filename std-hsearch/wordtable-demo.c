#include <stdio.h>
#include <stdlib.h>

#include "wordtable.h"

/*
 * This example is adapted from the man page for hsearch.
 * Annoyingly, that example has a single haswtable that made reuse of that code nearly impossible.
 * This one uses the _r() functions, which not only are able to work on different haswtables
 * but are also reentrant. Sadly, these are a bit GNU specific, but who doesn't use gcc? LOL
 */

static char *data[] = {"alpha", "bravo", "charlie", "delta",
                       "echo", "foxtrot", "golf", "hotel", "india", "juliet",
                       "kilo", "lima", "mike", "november", "oscar", "papa",
                       "quebec", "quebec", "romeo", "sierra", "tango", "uniform",
                       "victor", "whisky", "whisky", "x-ray", "yankee", "zulu", "zulu"
};


int main(void) {
    wordtable_t wtable;
    wordtable_init(&wtable, 50);
    int data_size = sizeof(data) / sizeof(char *);
    int i;

    /* insert all words to get word counts */
    for (int i = 0; i < data_size; i++) {
        wordentry_t *wp = wordtable_increment(&wtable, data[i]);
        printf("new word i=%d, data=%s, count=%ld, id=%p\n", i, data[i], wp->count, wp);
    }
    printf("\n");

    /* delete every 4th word */
    for (int i = 0; i < data_size; i += 4) {
        wordentry_t *wp = wordtable_decrement(&wtable, data[i]);
        printf("dec word i=%d, data=%s, count=%ld, id=%p\n", i, data[i], wp->count, wp);
    }
    printf("\n");

    for (int i = 0; i < data_size; i++) {
        wordentry_t *wp = wordtable_lookup(&wtable, data[i]);
        if (wp == NULL || wp->count == 0) continue;
        printf("non-zero word= %s, count=%ld, id=%p\n", data[i], wp->count, wp);
    }

    printf("\n");
    for (int i = 0; i < data_size; i++) {
        wordentry_t *wp = wordtable_lookup(&wtable, data[i]);
        if (wp == NULL || wp->count > 0) continue;
        printf("zero word= %s, count=%ld, id=%p\n", data[i], wp->count, wp);
    }

    for (int i = 0; i < data_size; i++) {
        int result = wordtable_delete_entry(&wtable, data[i]);
        printf("deleting word %s, result=%d\n", data[i], result);
    }
    wordtable_delete(&wtable);
    exit(EXIT_SUCCESS);
}
