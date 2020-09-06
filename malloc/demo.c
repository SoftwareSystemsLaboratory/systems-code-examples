#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main(int argc, char** argv) {
    const char* msg = "hello world";
    char *buffer = (char*)mymalloc(strlen(msg) + 1);
    memset(buffer, 0, strlen(msg)+1);
    strncpy(buffer, msg, strlen(msg)+1);
    printf("%s\n", buffer);
    myfree(buffer);
    return 0;
}
