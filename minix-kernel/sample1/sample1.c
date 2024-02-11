#include <stdio.h>
#include <stdlib.h>
#include <minix/syslib.h>

int main(int argc, char **argv) {
    sef_startup();

    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}
