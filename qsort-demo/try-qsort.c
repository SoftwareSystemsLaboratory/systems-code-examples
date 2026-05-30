#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Sort an array of pointers to structures. */

typedef struct wordcount_info_t {
    const char *word;
    int count;
} wordcount_info_t;


enum sort_order_enum {
    sort_order_ascending, sort_order_descending
};

int comparewordcount_info_t(enum sort_order_enum order, wordcount_info_t *left_entry, wordcount_info_t *right_entry) {
    switch (order) {
        case sort_order_descending:
            return -(left_entry->count - right_entry->count);
        case sort_order_ascending:
            return left_entry->count - right_entry->count;
        default:
            return left_entry->count - right_entry->count;
    }
}

static int qsort_cmp_wordcount(const void *left, const void *right) {
    wordcount_info_t *left_entry = *((wordcount_info_t **) left);
    wordcount_info_t *right_entry = *((wordcount_info_t **) right);
    return comparewordcount_info_t(sort_order_descending, left_entry, right_entry);
}

#define min(x, y) ( (x) < (y) ? (x) : (y) )


int main(int argc, char *argv[]) {
    const char *some_words[] = {"a", "b", "c", "d", "e", "beta", "gamma", "epsilon", "delta"};
    int some_counts[] = {8, 6, 7, 5, 3, -5, 25, 10, 3, 13, 17};

    const int some_words_size = sizeof(some_words) / sizeof(const char *);
    const int some_counts_size = sizeof(some_counts) / sizeof(int);
    const int items = min(some_words_size, some_counts_size);

    wordcount_info_t **word_counts = (wordcount_info_t **) malloc(items * sizeof(wordcount_info_t *));
    for (int i = 0; i < items; i++) {
        word_counts[i] = (wordcount_info_t *) malloc(sizeof(wordcount_info_t));
        word_counts[i]->word = some_words[i];
        word_counts[i]->count = some_counts[i];
    }

    printf("Word Array\n");
    for (int i = 0; i < items; i++) {
        printf("word %s: %d\n", word_counts[i]->word, word_counts[i]->count);
    }
    printf("\n");

    qsort(word_counts, items, sizeof(wordcount_info_t *), qsort_cmp_wordcount);

    printf("Sorted Word Array by Count\n");
    for (int i = 0; i < items; i++) {
        printf("{ word : '%s',  count : %d }\n", word_counts[i]->word, word_counts[i]->count);
    }
    printf("\n");

    printf("Search Results\n");
    for (int count = 0; count < 15; count++) {
        wordcount_info_t *search_key = (wordcount_info_t *) malloc(sizeof(wordcount_info_t));
        search_key->word = "any";
        search_key->count = count;
        wordcount_info_t **item = (wordcount_info_t **) bsearch(&search_key, word_counts, items,
                                                                sizeof(wordcount_info_t *), qsort_cmp_wordcount);
        if (item != NULL) {
            printf("{ word : '%s' : count : %d }\n", (*item)->word, (*item)->count);;
        }
        free(search_key);
    }
}
