#include "int_stack.h"
#include <stdio.h>


int main() {
    int_stack_t my_stack;
    const int capacity = 5;

    int_stack_init(&my_stack, capacity);

    for (int i = 0; i < capacity; i++) {
        int success = int_stack_push(&my_stack, i);
        if (!success) {
            fprintf(stderr, "Stack overflow: %d\n", i);
        }
    }

    int_stack_print(&my_stack, stdout);

    for (int i = 0; i < capacity; i++) {
        int top_value;
        int success = int_stack_pop(&my_stack, &top_value);
        if (!success) {
            fprintf(stderr, "Stack empty\n");
        }
    }

    int_stack_print(&my_stack, stdout);

    int_stack_push(&my_stack, 7);
    int_stack_push(&my_stack, 8);
    int_stack_print(&my_stack, stdout);
    int_stack_swap(&my_stack);
    int_stack_print(&my_stack, stdout);
    int_stack_add(&my_stack);
    int_stack_print(&my_stack, stdout);
    int_stack_dup(&my_stack);
    int_stack_print(&my_stack, stdout);
    int_stack_add(&my_stack);
    int_stack_print(&my_stack, stdout);
    return 0;
}
