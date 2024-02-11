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
        int_stack_push(&myStack, i);
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        printf("Popped value: %d\n", int_stack_pop(&myStack));
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);
    return 0;
}

