#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __USE_GNU

#define _GNU_SOURCE     /* Expose declaration of tdestroy() */

#include <search.h>
#include <time.h>


static char *data[] = {"alpha", "bravo", "charlie", "delta",
                       "echo", "foxtrot", "golf", "hotel", "india", "juliet",
                       "kilo", "lima", "mike", "november", "oscar", "papa",
                       "quebec", "quebec", "romeo", "sierra", "tango", "uniform",
                       "victor", "whisky", "whisky", "x-ray", "yankee", "zulu", "zulu"
};


typedef struct _wordinfo_t {
    char *word;
    int count;
} wordinfo_t;


static int compare_by_word(const void *pa, const void *pb) {
    const wordinfo_t *wi_a = pa, *wi_b = pb;

    //printf("comparing %s to %s\n", wi_a->word, wi_b->word);
    return strcmp(wi_a->word, wi_b->word);
}

static void action(const void *nodep, VISIT which, int depth) {
    //int *datap;
    wordinfo_t *datap;

    switch (which) {
        case preorder:
            break;
        case postorder:
            datap = *(wordinfo_t **) nodep;
            printf("word %s count %d depth %d\n", datap->word, datap->count, depth);
            break;
        case endorder:
            break;
        case leaf:
            datap = *(wordinfo_t **) nodep;
            printf("word %s count %d depth %d\n", datap->word, datap->count, depth);
            break;
    }
}

int main(void) {
    int i;
    wordinfo_t *ptr;
    wordinfo_t **val;
    int data_size = sizeof(data) / sizeof(char *);
    void *root = NULL;

    for (i = 0; i < data_size; i++) {
        printf("insert word %s\n", data[i]);
        ptr = (wordinfo_t *) malloc(sizeof(wordinfo_t));
        ptr->word = data[i];
        ptr->count = 0;
        if (ptr == NULL) break;
        val = (wordinfo_t **) tsearch((void *) ptr, &root, compare_by_word);
        if (val != NULL) {
            wordinfo_t *entry = *val;
            entry->count++;
        }
    }
    twalk(root, action);
    tdestroy(root, free);
    exit(EXIT_SUCCESS);
}
