#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This example shows how to sort an array of pointers to an underlying structure type.
 * Can easly be adapted for other needs!
 */

typedef struct wordcount_info_t
{
    const char *word;
    int count;
} wordcount_info_t;


enum sort_order_enum { sort_order_ascending, sort_order_descending };

int comparewordcount_info_t(enum sort_order_enum order, wordcount_info_t * wcA, wordcount_info_t * wcB)
{
    //printf("A=%s/%d B=%s/%d\n", wcA->word, wcA->count, wcB->word, wcB->count);
    switch (order)
    {
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
    /* these fixed size arrays are being used to populate a dynamic one */
    const char* some_words[] = { "a", "b", "c", "d", "e", "beta", "gamma", "epsilon", "delta" };
    int some_counts[] = { 8, 6, 7, 5, 3, -5, 25, 10, 3, 13, 17 };

    /* shows how to find the number of elements in an array without hard-coding */
    const int some_words_size = sizeof(some_words) / sizeof(const char*);
    const int some_counts_size = sizeof(some_counts) / sizeof(int);
    const int items = min(some_words_size, some_counts_size);

    /* use this to create dynamic array of words and their counts */
    /* note: this is not intended to be a wordcount program. There's intentionally no I/O */

    wordcount_info_t **word_counts = (wordcount_info_t **) malloc(items * sizeof(wordcount_info_t*));
    for (int i=0; i < items; i++)
    {
        word_counts[i] = (wordcount_info_t *)malloc(sizeof(wordcount_info_t));
        word_counts[i]->word = some_words[i];
        word_counts[i]->count = some_counts[i];
    }

    printf("Word Array\n");
    for (int i=0; i < items; i++)
    {
        printf("word %s: %d\n", word_counts[i]->word, word_counts[i]->count);
    }
    printf("\n");

    /* perform general qsort() using library function - sort by the wordcount field, descending */
    qsort(word_counts, items, sizeof(wordcount_info_t*), qsort_cmp_wordcount);

    printf("Sorted Word Array by Count\n");
    for (int i=0; i < items; i++)
    {
        printf("{ word : '%s',  count : %d }\n", word_counts[i]->word, word_counts[i]->count);
    }
    printf("\n");

    /* use general bsearch() using library function -  requires data to be sorted */
    /* because we use the same comparison function for qsort() and bsearch(), we can do a bsearch() on data in ascending or descending order */
    printf("Search Results\n");
    for (int count=0; count < 15; count++)
    {
        wordcount_info_t *search_key = (wordcount_info_t *)malloc(sizeof(wordcount_info_t));
        search_key->word = "any";
        search_key->count = count;
        wordcount_info_t **item = (wordcount_info_t **) bsearch (&search_key, word_counts, items, sizeof (wordcount_info_t*), qsort_cmp_wordcount);
        if (item != NULL)
        {
            printf("{ word : '%s' : count : %d }\n", (*item)->word, (*item)->count);;
        }
        free(search_key);
    }
}

