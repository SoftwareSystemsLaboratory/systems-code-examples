#include "list.hh"
#include "debug.hh"
#include "tests.hh"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int pass_count = run_tests();

    printf("%d tests passed\n", pass_count);

    return 0;
}
