/* Credit: https://www.lemoda.net/c/unix-regex/ */
/* Credit: GNU C docs */
/* Credit to self for fixing some problems with handling on OS X and Linux */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "regex-match.h"

int main (int argc, char ** argv)
{
    regex_t regex;
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
    basic_matchlist_t match_list;
    regex_compile (&regex, regex_text);
    basic_matchlist_init(&match_list);
    regex_match (&regex, find_text, &match_list);
    basic_matchlist_print(&match_list);
    basic_matchlist_delete(&match_list);
    regfree (&regex);
    return 0;
}
