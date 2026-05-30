#include "debug.hh"
#include <stdio.h>

int assert_equals(int expected, int actual, const char *msg)
{
    int result;
    if(expected == actual)
    {
        result = 1;
    }
    else
    {
        result = 0;
        printf("%s", msg);
    }
    return result;
}

int assert_equals(int expected, int actual)
{
    return assert_equals(expected, actual, "");
}
