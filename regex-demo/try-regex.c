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

void process_regex(const char *find_text, const char *regex_text);

int main(int argc, char **argv) {
    int eof;
    const char *regex_text = WORD_REGEX;

    // if no arguments read text from stdin; else use argv[1] as text
    if (argc < 2) {
        strbuffer_t buffer;
        strbuffer_init(&buffer, 80, 10);
        char *line = strbuffer_getline(&buffer, &eof);
        process_regex(line, regex_text);
        if (line) free(line);
    } else {
        process_regex(argv[1], regex_text);
    }
    return 0;
}

void process_regex(const char *find_text, const char *regex_text) {
    regex_t regex;
    basic_matchlist_t match_list;
    regex_compile(&regex, regex_text);
    basic_matchlist_init(&match_list);
    regex_match(&regex, find_text, &match_list);
    basic_matchlist_print(&match_list);
    basic_matchlist_delete(&match_list);
    regfree(&regex);
}
