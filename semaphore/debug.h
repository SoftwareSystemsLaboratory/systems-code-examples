#ifndef DEBUG_HH
#define DEBUG_HH

#include <stdio.h>
#include <stdlib.h>

#define assertmsg(x,msg) if(!(x)) { printf("assertion ["); printf(#x); printf("] fails (%s:%d - %s) ", __FILE__, __LINE__, __FUNCTION__); printf(#msg); printf("\n"); exit(1); }

#define assert(x) assertmsg(x, nomsg)

int assertEquals(int expected, int actual, const char *msg);
int assertEquals(int expected, int actual);

#endif

