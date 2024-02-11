#include <stdio.h>
#include <stdlib.h>

#include "wordtable.h"

void wordtable_init(wordtable_t *wt_ptr, int size) {
    hcreate_r(size, &wt_ptr->wtable);
    wt_ptr->size = size;
}

wordentry_t *wordtable_lookup(wordtable_t *wt_ptr, char *word) {
    ENTRY e, *ep;
    e.key = word;
    hsearch_r(e, FIND, &ep, &wt_ptr->wtable);
    return ep ? (wordentry_t *) ep->data : NULL;
}


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

/* hsearch, unfortunately, doesn't support deletion. But we can at least make a word unavailable */
/* and free up the wordcount_t entry for it */

int wordtable_delete_entry(wordtable_t *wt_ptr, char *word) {
    ENTRY e, *ep;
    e.key = word;
    hsearch_r(e, FIND, &ep, &wt_ptr->wtable);
    if (ep != NULL) {
        wordentry_t *wp = ep->data;
        free(ep->data);
        ep->data = NULL;
        return wp != NULL;
    }
    return 0;
}


wordentry_t *wordtable_decrement(wordtable_t *wt_ptr, char *word) {
    return wordtable_upsert(wt_ptr, word, -1);
}


wordentry_t *wordtable_increment(wordtable_t *wt_ptr, char *word) {
    return wordtable_upsert(wt_ptr, word, 1);
}

void wordtable_delete(wordtable_t *wt_ptr) {
    hdestroy_r(&wt_ptr->wtable);
}


