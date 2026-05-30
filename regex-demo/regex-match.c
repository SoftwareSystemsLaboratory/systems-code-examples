
/* Based on examples from GNU C docs and lemoda.net. */

#include "regex-match.h"

#include <string.h>


void basic_matchlist_add(basic_matchlist_t *head_ptr, int start, int finish, char *matched_text) {
    basic_matchinfo_t *my_entry = malloc(sizeof(basic_matchinfo_t));
    my_entry->start = start;
    my_entry->finish = finish;
    my_entry->matched_text = matched_text;
    TAILQ_INSERT_TAIL(head_ptr, my_entry, entries);
}

void basic_matchlist_print(basic_matchlist_t *head_ptr) {
    basic_matchinfo_t *np;
    TAILQ_FOREACH(np, head_ptr, entries) {
        printf("(%d,%d): %s\n", np->start, np->finish, np->matched_text);
    }
}

void basic_matchlist_delete(basic_matchlist_t *head_ptr) {
    basic_matchinfo_t *n1, *n2;
    n1 = TAILQ_FIRST(head_ptr);
    while (n1 != NULL) {
        n2 = TAILQ_NEXT(n1, entries);
        free(n1->matched_text);
        free(n1);
        n1 = n2;
    }
}

void basic_matchlist_init(basic_matchlist_t *head_ptr) {
    basic_matchlist_t head = TAILQ_HEAD_INITIALIZER(head);
    *head_ptr = head;
    TAILQ_INIT(head_ptr);
}

#define MAX_ERROR_MSG 0x1000

int regex_compile(regex_t *r, const char *regex_text) {
#ifdef WITH_APPLE
    int status = regcomp(r, regex_text, REG_EXTENDED | REG_ENHANCED | REG_NEWLINE);
#endif
#ifdef WITH_LINUX
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
#endif
    if (status != 0) {
        char error_message[MAX_ERROR_MSG];
        regerror(status, r, error_message, MAX_ERROR_MSG);
        printf("Regex error compiling '%s': %s\n",
               regex_text, error_message);
        return 1;
    }
    return 0;
}

static void record_match(const char *to_match, const char *match_start,
                         regmatch_t *match, basic_matchlist_t *match_list) {
    int start = match->rm_so + (match_start - to_match);
    int finish = match->rm_eo + (match_start - to_match);
    char *matched_text = strndup(to_match + start, finish - start);
    basic_matchlist_add(match_list, start, finish, matched_text);
}

int regex_match(regex_t *r, const char *to_match, basic_matchlist_t *match_list) {
    const char *p = to_match;
    const int n_matches = 10;
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec(r, p, n_matches, m, 0);
        if (nomatch) {
            return nomatch;
        }
        for (i = 0; i < n_matches; i++) {
            if (m[i].rm_so == -1) {
                break;
            }

            record_match(to_match, p, &m[i], match_list);
            break;
        }

        p += m[0].rm_eo;
    }
    return 0;
}
