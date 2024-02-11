#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#define _GNU_SOURCE

#include <search.h>

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


typedef struct _wordtable_t {
    struct hsearch_data wtable;
} wordtable_t;

typedef struct _wordentry_t {
    char *word;
    long count;
} wordentry_t;

void wordtable_init(wordtable_t *wt_ptr) {
    hcreate_r(30, &wt_ptr->wtable);
}

wordentry_t *wordtable_lookup(wordtable_t *wt_ptr, char *word) {
    ENTRY e, *ep;
    e.key = word;
    hsearch_r(e, FIND, &ep, &wt_ptr->wtable);
    return ep ? (wordentry_t *) ep->data : NULL;
}

/*
long haswtable_adjust(struct hsearch_data* ht_ptr, char* word, int delta) {
    if (ep != NULL) {
       long new_count = delta + (long)ep->data;
       new_count = new_count >= 0 ? new_count : 0;
       ep->data = (void*) new_count;
       return new_count;
    }

    hsearch_r(e, ENTER, &ep, ht_ptr);
    if (ep == NULL) {
       fprintf(stderr, "entry failed\n");
       exit(EXIT_FAILURE);
    }
    return (long)ep->data;
}
*/

wordentry_t *wordtable_upsert(wordtable_t *wt_ptr, char *word, int delta) {
    wordentry_t *wp = wordtable_lookup(wt_ptr, word);
    if (wp != NULL) {
        //printf("Found word %s, count = %ld, address %p\n", wp->word, wp->count, wp);
        if (wp->count > 0) wp->count += delta;
        return wp;
    } else {
        ENTRY e, *ep;
        wp = (wordentry_t *) malloc(sizeof(wordentry_t));
        wp->word = word;
        wp->count = 1L;
        e.key = word;
        e.data = wp;
        hsearch_r(e, ENTER, &ep, &wt_ptr->wtable);
        //printf("new word %s, count = %ld, address = %p\n", wp->word, wp->count, wp);
        return ep == NULL ? NULL : wp;
    }
}


/*
long haswtable_decrement(struct hsearch_data* ht_ptr, char* word) {
   return haswtable_adjust(ht_ptr, word, -1);
}
long haswtable_increment(struct hsearch_data* ht_ptr, char* word) {
   return haswtable_adjust(ht_ptr, word, 1);
}
*/

wordentry_t *wordtable_decrement(wordtable_t *wt_ptr, char *word) {
    return wordtable_upsert(wt_ptr, word, -1);
}


wordentry_t *wordtable_increment(wordtable_t *wt_ptr, char *word) {
    return wordtable_upsert(wt_ptr, word, 1);
}

/*
void haswtable_delete(struct hsearch_data* ht_ptr) {
    hdestroy_r(ht_ptr);
}
*/

void wordtable_delete(wordtable_t *wt_ptr) {

    hdestroy_r(&wt_ptr->wtable);
}


int main(void) {
    wordtable_t wtable;
    wordtable_init(&wtable);
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
    wordtable_delete(&wtable);
    exit(EXIT_SUCCESS);
}
