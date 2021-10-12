/*
 * Many students come to C from Java.
 *
 * This is a demonstration of how to create a StringBuffer lite in C.
 * The buffer is used by declaring a cbuffer_t, which acts as a handle for all operations.
 */

#ifndef _CBUFFER_H_
#define _CBUFFER_H_

typedef struct _cbuffer_t {
    struct charlist_t charlist;
    int pos;
} cbuffer_t;

#
extern void cbuffer_new(cbuffer_t* buffer);

void cbuffer_add(cbuffer_t* buffer, char c);

#endif
