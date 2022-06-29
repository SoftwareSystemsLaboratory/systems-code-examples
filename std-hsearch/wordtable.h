#ifndef _HSEARCH_WORDINFO_H_
#define _HSEARCH_WORDINFO_H_

#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#define _GNU_SOURCE

#include <search.h>

typedef struct _wordtable_t
{
    struct hsearch_data wtable;
    int size;
} wordtable_t;

typedef struct _wordentry_t
{
    char* word;
    long count;
} wordentry_t;

extern void wordtable_init(wordtable_t* wt_ptr, int size);
extern wordentry_t* wordtable_lookup(wordtable_t* wt_ptr, char* word);
extern wordentry_t* wordtable_upsert(wordtable_t* wt_ptr, char* word, int delta);
extern wordentry_t* wordtable_decrement(wordtable_t* wt_ptr, char* word);
extern wordentry_t* wordtable_increment(wordtable_t* wt_ptr, char* word);
extern void wordtable_delete(wordtable_t* wt_ptr);
extern int wordtable_delete_entry(wordtable_t* wt_ptr, char* word);

#endif
