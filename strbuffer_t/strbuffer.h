/*
 * Many students come to C from Java.
 *
 * This is a demonstration of how to create a StringBuffer lite in C.
 * The buffer is used by declaring a strbuffer_t, which acts as a handle for all operations.
 */

#ifndef _STRINGBUFFER_H_
#define _STRINGBUFFER_H_

typedef struct _strbuffer_t
{
    char* data;
    int capacity;
    int increment;
    int pos;
} strbuffer_t;

#define MIN_CAPACITY 80
#define MIN_INCREMENT 10

extern void strbuffer_new(strbuffer_t* buffer);

extern void strbuffer_init(strbuffer_t* buffer, int capacity, int increment);

extern void strbuffer_resize_if_needed(strbuffer_t* buffer);

extern void strbuffer_append(strbuffer_t* buffer, char c);

extern char* strbuffer_tostring(strbuffer_t* buffer);

extern void strbuffer_reset(strbuffer_t* buffer);

extern char* strbuffer_getline(strbuffer_t* buffer, int *eof);


#endif
