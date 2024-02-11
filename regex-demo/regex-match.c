
/* Credit: https://www.lemoda.net/c/unix-regex/ */
/* Credit: GNU C docs */
/* Credit to self for fixing some problems with handling on OS X and Linux */
/* Credit to self for finding a nicer way to separate matching code from
 * match results
 */

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
    /* create a tail queue */
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

/*
  Match the string in "to_match" against the compiled regular
  expression in "r".
 */

int regex_match(regex_t *r, const char *to_match, basic_matchlist_t *match_list) {
    const char *p = to_match;
    const int n_matches = 10;
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec(r, p, n_matches, m, 0);
        if (nomatch) {
            //printf ("No more matches.\n");
            return nomatch;
        }
        //printf("nomatch = %d\n", nomatch);
        for (i = 0; i < n_matches; i++) {
            int start;
            int finish;
            if (m[i].rm_so == -1) {
                break;
            }

            start = m[i].rm_so + (p - to_match);
            finish = m[i].rm_eo + (p - to_match);
            char *matched_text = strndup(to_match + start, finish - start);
            //printf("Match %d at %d, %d\n", i, m[i].rm_so, m[i].rm_eo);
            basic_matchlist_add(match_list, start, finish, matched_text);
            break;
        }

        p += m[0].rm_eo;
    }
    return 0;
}

/*
int main (int argc, char ** argv)
{
    regex_t r;
    const char * regex_text;
    const char * find_text;
    if (argc != 3) {
        //regex_text = "([[:digit:]]+)[^[:digit:]]+([[:digit:]]+)";
        regex_text = "(\\w+)";
        find_text = "All cows eat grass. Call 773.555.1212.";
    }
    else {
        regex_text = argv[1];
        find_text = argv[2];
    }
    printf ("Trying to find '%s' in '%s'\n", regex_text, find_text);
    compile_regex (& r, regex_text);
    basic_matchlist_t match_list;
    basic_matchlist_init(&match_list);
    match_regex (& r, find_text, &match_list);
    basic_matchlist_print(&match_list);
    regfree (& r);
    return 0;
}
*/

