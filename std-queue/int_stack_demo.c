// main.c
#include "int_stack.h"
#include <stdio.h>


int main() {
    int_stack_t my_stack;
    const int capacity = 5;

    // Initialize the stack with a capacity of 5.
    int_stack_init(&my_stack, capacity);

    // Push values onto the stack.
    for (int i = 0; i < capacity; i++) {
        int success = int_stack_push(&my_stack, i);
        if (!success) {
            fprintf(stderr, "Stack overflow: %d\n", i);
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&my_stack, stdout);

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        int top_value;
        int success = int_stack_pop(&my_stack, &top_value);
        if (!success) {
            fprintf(stderr, "Stack empty\n");
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&my_stack, stdout);

    // Quick tests for swap, dup, and add.

    int_stack_push(&my_stack, 7);
    int_stack_push(&my_stack, 8);
    int_stack_print(&my_stack, stdout);
    int_stack_swap(&my_stack);
    int_stack_print(&my_stack, stdout);
    int_stack_add(&my_stack);
    int_stack_print(&my_stack, stdout); // hopefully, 15 only item on stack!
    int_stack_dup(&my_stack);
    int_stack_print(&my_stack, stdout); // hopefully, 15 only item on stack!
    int_stack_add(&my_stack);
    int_stack_print(&my_stack, stdout); // hopefully, 30 only item on stack!
    return 0;
}
