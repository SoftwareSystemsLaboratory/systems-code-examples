#include "debug.hh"
#include <stdio.h>

int assertEquals(int expected, int actual, const char *msg) {
    int result;
    if(expected == actual) {
        result = 1;
    } else {
        result = 0;
        printf(msg);
    }
    return result;
}

int assertEquals(int expected, int actual) {
    return assertEquals(expected, actual, "");
}
