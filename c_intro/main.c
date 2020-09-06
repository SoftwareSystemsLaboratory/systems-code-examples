#include "list.hh"
#include "debug.hh"
#include "tests.hh"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int passCount = runTests();

    printf("%d tests passed\n", passCount);

    return 0;
}
