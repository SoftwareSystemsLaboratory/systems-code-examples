#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This example shows how to sort an array of pointers to an underlying structure type.
 * Can easly be adapted for other needs!
 */

typedef struct wordcount_info_t {
    const char *word;
    int count;
} wordcount_info_t;


enum sort_order_enum { sort_order_ascending, sort_order_descending };

int comparewordcount_info_t(enum sort_order_enum order, wordcount_info_t * wcA, wordcount_info_t * wcB) {
    //printf("A=%s/%d B=%s/%d\n", wcA->word, wcA->count, wcB->word, wcB->count);
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
    //printf("Comparing %p amd %p\n", p1, p2);
    wordcount_info_t * w1 = *((wordcount_info_t **) p1);
    wordcount_info_t * w2 = *((wordcount_info_t **) p2);
    return comparewordcount_info_t(sort_order_descending, w1, w2);
}

#define min(x, y) ( (x) < (y) ? (x) : (y) )


int main(int argc, char *argv[])
{
    const char* some_words[] = { "a", "b", "c", "d", "e", "beta", "gamma", "epsilon", "delta" };
    int some_counts[] = { 8, 6, 7, 5, 3, -5, 25, 10, 3, 13, 17 };

    const int some_words_size = sizeof(some_words) / sizeof(const char*);
    const int some_counts_size = sizeof(some_counts) / sizeof(int);
    const int items = min(some_words_size, some_counts_size);

    wordcount_info_t **word_counts = (wordcount_info_t **) malloc(items * sizeof(wordcount_info_t*));
    for (int i=0; i < items; i++) {
        word_counts[i] = (wordcount_info_t *)malloc(sizeof(wordcount_info_t));
        word_counts[i]->word = some_words[i];
        word_counts[i]->count = some_counts[i];
    }

    printf("Original word list\n");
    for (int i=0; i < items; i++) {
        printf("word %s: %d\n", word_counts[i]->word, word_counts[i]->count);
    }

    qsort(word_counts, items, sizeof(wordcount_info_t*), qsort_cmp_wordcount);

    printf("Sorted word list\n");
    for (int i=0; i < items; i++) {
        printf("word %s: %d\n", word_counts[i]->word, word_counts[i]->count);
    }

    printf("Search results\n");
    for (int count=0; count < 15; count++) {
        wordcount_info_t *search_key = (wordcount_info_t *)malloc(sizeof(wordcount_info_t));
        search_key->word = "any";
        search_key->count = count;
        wordcount_info_t **item = (wordcount_info_t **) bsearch (&search_key, word_counts, items, sizeof (wordcount_info_t*), qsort_cmp_wordcount);
        if (item != NULL)  {
            printf("Found count %d for word %s\n", (*item)->count, (*item)->word);;
        } else {
            printf("Not found count value %d \n", count);
        }
        free(search_key);
    }
}

