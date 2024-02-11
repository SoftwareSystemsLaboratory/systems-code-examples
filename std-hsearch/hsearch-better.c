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
                       "quebec", "quebec", "romeo", "sierra", "tango", "uniform",
                       "victor", "whisky", "whisky", "x-ray", "yankee", "zulu", "zulu"
};


void wordtable_init(struct hsearch_data *ht_ptr) {
    hcreate_r(30, ht_ptr);
}

ENTRY *wordtable_lookup(struct hsearch_data *ht_ptr, char *word) {
    ENTRY e, *ep;
    e.key = word;
    hsearch_r(e, FIND, &ep, ht_ptr);
    return ep;
}

long wordtable_adjust(struct hsearch_data *ht_ptr, char *word, int delta) {
    ENTRY e, *ep;
    e.key = word;
    e.data = (void *) 1L;
    ep = wordtable_lookup(ht_ptr, word);
    /* if entry exists, increment it */
    if (ep != NULL) {
        long new_count = delta + (long) ep->data;
        new_count = new_count >= 0 ? new_count : 0;
        ep->data = (void *) new_count;
        return new_count;
    }

    hsearch_r(e, ENTER, &ep, ht_ptr);
    if (ep == NULL) {
        fprintf(stderr, "entry failed\n");
        exit(EXIT_FAILURE);
    }
    return (long) ep->data;
}

long wordtable_decrement(struct hsearch_data *ht_ptr, char *word) {
    return wordtable_adjust(ht_ptr, word, -1);
}

long wordtable_increment(struct hsearch_data *ht_ptr, char *word) {
    return wordtable_adjust(ht_ptr, word, 1);
}

void wordtable_delete(struct hsearch_data *ht_ptr) {
    hdestroy_r(ht_ptr);
}


int main(void) {
    struct hsearch_data htable;
    wordtable_init(&htable);

    int data_size = sizeof(data) / sizeof(char *);
    int i;

    printf("insertions:\n");
    /* insert all words to get word counts */
    for (int i = 0; i < data_size; i++) {
        long new_count = wordtable_increment(&htable, data[i]);
        printf("incremented word i=%d, data=%s, count=%ld\n", i, data[i], new_count);
    }

    printf("\n");
    printf("insertions:\n");
    /* delete every 4th word */
    for (int i = 0; i < data_size; i += 4) {
        long new_count = wordtable_decrement(&htable, data[i]);
        printf("decrementing word i=%d, data=%s, count=%ld\n", i, data[i], new_count);
    }

    printf("\n");

    printf("non-zero words:\n");
    for (int i = 0; i < data_size; i++) {
        ENTRY *ep = wordtable_lookup(&htable, data[i]);
        if (ep == NULL) continue;
        long ep_count = (long) (ep->data);
        if (ep_count == 0) continue;
        printf("word= %s, count=%ld\n", data[i], ep_count);
    }

    printf("\n");
    printf("zero words:\n");
    for (int i = 0; i < data_size; i++) {
        ENTRY *ep = wordtable_lookup(&htable, data[i]);
        long ep_count = ep == NULL ? 0L : (long) (ep->data);
        if (ep_count > 0) continue;
        printf("word= %s, count=%ld\n", data[i], ep_count);
    }
    hdestroy_r(&htable);
    exit(EXIT_SUCCESS);
}
