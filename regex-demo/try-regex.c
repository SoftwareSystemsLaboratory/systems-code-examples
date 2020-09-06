/* Credit: https://www.lemoda.net/c/unix-regex/ */
/* Credit: GNU C docs */
/* Credit to self for fixing some problems with handling on OS X and Linux */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 0x1000

static int compile_regex (regex_t * r, const char * regex_text)
{
#ifdef WITH_APPLE
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_ENHANCED|REG_NEWLINE);
#endif
#ifdef WITH_LINUX
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
#endif
    if (status != 0) {
        char error_message[MAX_ERROR_MSG];
        regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n",
                regex_text, error_message);
        return 1;
    }
    return 0;
}

/*
  Match the string in "to_match" against the compiled regular
  expression in "r".
 */

static int match_regex (regex_t * r, const char * to_match)
{
    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char * p = to_match;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 10;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            printf ("No more matches.\n");
            return nomatch;
        }
        for (i = 0; i < n_matches; i++) {
            int start;
            int finish;
            if (m[i].rm_so == -1) {
                break;
            }

            /* rm_so (starting offset of match) adn rm_eo (end offset of match) */
            start = m[i].rm_so + (p - to_match);
            finish = m[i].rm_eo + (p - to_match);
            if (i == 0) {
                printf ("$& is ");
            }
            else {
                printf ("$%d is ", i);
            }
            char* matched_text = strndup(to_match+start, finish-start);
            printf ("'%.*s' (bytes %d:%d)\n", (finish - start),
                    to_match + start, start, finish);
            printf("matched %s\n", matched_text);
        }

        p += m[0].rm_eo;
    }
    return 0;
}

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
    match_regex (& r, find_text);
    regfree (& r);
    return 0;
}
