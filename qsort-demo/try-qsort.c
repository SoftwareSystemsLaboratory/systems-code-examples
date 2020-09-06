#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This example shows how to sort an array of pointers to an underlying structure type.
 * Can easly be adapted for other needs!
 */

typedef struct _wordcount_info_t {
    char *word;
    int count;
} _wordcount_info_t, *wordcount_info_t;


enum sort_order_enum { sort_order_ascending, sort_order_descending };

int compare_wordcount_info_t(enum sort_order_enum order, void* itemA, void* itemB) {
    wordcount_info_t wcA, wcB;
    wcA = (wordcount_info_t) itemA;
    wcB = (wordcount_info_t) itemB;
    switch (order) {
    case sort_order_descending:
        return -(wcA->count - wcB->count);
    case sort_order_ascending:
        return wcA->count - wcB->count;
    default: /* also sort_order_ascending */
        return wcA->count - wcB->count;
    }
}

static int qsort_cmp_wordcount(const void *p1, const void *p2)
{
    return compare_wordcount_info_t(sort_order_descending, * (wordcount_info_t * const *) p1, * (wordcount_info_t * const *) p2);
}

#define min(x, y) ( (x) < (y) ? (x) : (y) )


int main(int argc, char *argv[])
{
    const char* some_words[] = { "a", "b", "c", "d", "e" };
    int some_counts[] = { 8, 6, 7, 5, 3 };

    const int some_words_size = sizeof(some_words) / sizeof(char*);
    const int some_counts_size = sizeof(some_counts) / sizeof(int);
    const int items = min(some_words_size, some_counts_size);

    wordcount_info_t* word_counts = (wordcount_info_t*) malloc(items * sizeof(wordcount_info_t));
    for (int i=0; i < items; i++) {
        word_counts[i] = (wordcount_info_t)malloc(sizeof(_wordcount_info_t));
        word_counts[i]->word = strdup(some_words[i]);
        word_counts[i]->count = some_counts[i];
    }

    qsort(word_counts, items, sizeof(wordcount_info_t), qsort_cmp_wordcount);

    for (int i=0; i < items; i++) {
        printf("word %s: %d\n", word_counts[i]->word, word_counts[i]->count);
    }

    /* free up dynamic array and strings */
    for (int i=0; i < items; i++)
        free(word_counts[i]->word);
    free(word_counts);
}

