// int_stack.h - interface to the int_stack

#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} int_entry_t;

typedef struct int_stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} int_stack_t;

void int_stack_init(int_stack_t *stk, int capacity);
int int_stack_push(int_stack_t *stk, int value);
int int_stack_pop(int_stack_t *stk, int *top_value);
int int_stack_top(int_stack_t *stk, int *top_value);
void int_stack_print(int_stack_t *stk, FILE *file);


#endif // INT_STACK_H

