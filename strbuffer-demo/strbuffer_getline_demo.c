#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * This example shows a strbuffer_t-enabled getline() like function
 * and how to use strtok() to separate text with whitespace delimiters.
 */

#include "strbuffer.h"

#define DELIMS " \n\r\t"

int main(int argc, char *argv[]) {
    strbuffer_t buffer;
    strbuffer_init(&buffer, 80, 10);
    for (;;) {
        int eof;
        char *line = strbuffer_getline(&buffer, &eof);
        if (eof) break;
        char *next_word = strtok(line, DELIMS);
        while (next_word != NULL) {
            printf("word: %s\n", next_word);
            next_word = strtok(NULL, DELIMS);
        }
        free(line);
    }
}
