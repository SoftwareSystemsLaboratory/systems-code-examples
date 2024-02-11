#include <stdio.h>
#include <stdlib.h>

#include "wordlist.h"

int main(int argc, char *argv[]) {

    struct wordlist_t wordlist;
    wordlist_init(&wordlist);

    /* add each argument (after 0) to queue; just keep pointer */
    for (int i = 1; i < argc; i++) {
        wordlist_add(&wordlist, argv[i]);
    }

    wordlist_print(&wordlist);
    wordlist_delete(&wordlist);
}
