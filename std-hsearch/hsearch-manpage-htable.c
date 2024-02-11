#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#define _GNU_SOURCE

#include <search.h>

/*
 * This example is adapted from the man page for hsearch.
 * Annoyingly, that example has a single hashtable that made reuse of that code nearly impossible.
 * This one uses the _r() functions, which not only are able to work on different hashtables
 * but are also reentrant. Sadly, these are a bit GNU specific, but who doesn't use gcc? LOL
 */

static char *data[] = {"alpha", "bravo", "charlie", "delta",
                       "echo", "foxtrot", "golf", "hotel", "india", "juliet",
                       "kilo", "lima", "mike", "november", "oscar", "papa",
                       "quebec", "romeo", "sierra", "tango", "uniform",
                       "victor", "whisky", "x-ray", "yankee", "zulu"
};

int main(void) {
    int i;
    ENTRY e, *ep;
    struct hsearch_data htable;

    hcreate_r(30, &htable);

    for (i = 0; i < 24; i++) {
        e.key = data[i];
        e.data = (void *) (i + 0L);
        hsearch_r(e, ENTER, &ep, &htable);
        if (ep == NULL) {
            fprintf(stderr, "entry failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 22; i < 26; i++) {
        e.key = data[i];
        hsearch_r(e, FIND, &ep, &htable);
        printf("%9.9s -> %9.9s:%ld\n", e.key,
               ep ? ep->key : "NULL", ep ? (long) (ep->data) : 0);
    }
    hdestroy_r(&htable);
    exit(EXIT_SUCCESS);
}
