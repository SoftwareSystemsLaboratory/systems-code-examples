/* Credit: https://www.lemoda.net/c/unix-regex/ */
/* Credit: GNU C docs */
/* Credit to self for fixing some problems with handling on OS X and Linux */


#define WORD_REGEX "(\\w+)"
#define ALT_WORD_REGEX "([[:digit:]]+)[^[:digit:]]+([[:digit:]]+)" // not used (yet)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "strbuffer.h"
#include "regex-match.h"

int main (int argc, char ** argv)
{
    regex_t regex;
    const char * regex_text = WORD_REGEX;
    const char * find_text;
    const char * line = NULL;
    strbuffer_t buffer;
    int eof;

    // if no arguments read text from stdin; else use argv[1] as text
    if (argc < 2) {
        strbuffer_init(&buffer, 80, 10);
        line = strbuffer_getline(&buffer, &eof);
        find_text = line;
    }
    else {
        find_text = argv[1];
    }
    printf ("Trying to find '%s' in '%s'\n", regex_text, find_text);
    basic_matchlist_t match_list;
    regex_compile (&regex, regex_text);
    basic_matchlist_init(&match_list);
    regex_match (&regex, find_text, &match_list);
    basic_matchlist_print(&match_list);
    basic_matchlist_delete(&match_list);
    regfree (&regex);
    if (line) free(line);
    return 0;
}
