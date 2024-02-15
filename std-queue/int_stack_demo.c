// main.c
#include "int_stack.h"
#include <stdio.h>


int main() {
    int_stack_t myStack;
    const int capacity = 5;

    // Initialize the stack with a capacity of 5.
    int_stack_init(&myStack, capacity);

    // Push values onto the stack.
    for (int i = 0; i < capacity; i++) {
        int success = int_stack_push(&myStack, i);
        if (!success) {
            fprintf(stderr, "Stack overflow: %d\n", i);
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        int top_value;
        int success = int_stack_pop(&myStack, &top_value);
        if (!success) {
            fprintf(stderr, "Stack empty\n");
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);

    // Quick tests for swap, dup, and add.

    int_stack_push(&myStack, 7);
    int_stack_push(&myStack, 8);
    int_stack_print(&myStack, stdout);
    int_stack_swap(&myStack);
    int_stack_print(&myStack, stdout);
    int_stack_add(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 15 only item on stack!
    int_stack_dup(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 15 only item on stack!
    int_stack_add(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 30 only item on stack!
    return 0;
}

