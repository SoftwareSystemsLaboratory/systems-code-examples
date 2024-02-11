#include <stdio.h>
#include <stdlib.h>

#include "strbuffer.h"

int main(int argc, char *argv[]) {
    strbuffer_t buffer;
    strbuffer_init(&buffer, 20, 10);
    for (int letter = 'A'; letter <= 'Z'; letter++) {
        strbuffer_reset(&buffer);
        for (int i = 0; i < 300; i++) {
            strbuffer_append(&buffer, letter);
            char *text = strbuffer_tostring(&buffer);
            printf("text = %s\n", text);
            printf("buffer capacity = %d, pos = %d, increment = %d\n", buffer.capacity, buffer.pos, buffer.increment);
            free(text);
        }
    }
}


