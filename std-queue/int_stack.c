#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

void int_stack_init(int_stack_t *stack, int capacity) {
    SLIST_INIT(&stack->head);
    stack->size = 0;
    stack->capacity = capacity;
}

int int_stack_push(int_stack_t *stack, int value) {
    if (stack->size >= stack->capacity) {
        printf("Stack is at full capacity.\n");
        return 0;
    }

    int_entry_t *new_entry = malloc(sizeof(int_entry_t));
    if (new_entry) {
        new_entry->value = value;
        SLIST_INSERT_HEAD(&stack->head, new_entry, entries);
        stack->size++;
        return 1;
    }
    return 0;
}

int int_stack_pop(int_stack_t *stack, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stack->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stack->head, entries);
        free(entry);
        stack->size--;
        *top_value = value;
        return 1;
    }
    return 0;
}

int int_stack_top(int_stack_t *stack, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stack->head);
    if (entry) {
        *top_value = entry->value;
        return 1;
    }
    return 0;
}

int int_stack_dup(int_stack_t *stack) {
    if (stack->size < 1)
        return 0;
    int top_value;
    int_stack_top(stack, &top_value);
    return int_stack_push(stack, top_value);
}

int int_stack_swap(int_stack_t *stack) {
    if (stack->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stack, &top_value);
    int_stack_pop(stack, &next_to_top_value);
    int_stack_push(stack, top_value);
    return int_stack_push(stack, next_to_top_value);
}

int int_stack_add(int_stack_t *stack) {
    if (stack->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stack, &top_value);
    int_stack_pop(stack, &next_to_top_value);
    return int_stack_push(stack, top_value + next_to_top_value);
}

void int_stack_print(int_stack_t *stack, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stack->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stack->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stack) {
    return stack->size;
}

int int_stack_capacity(int_stack_t* stack) {
    return stack->capacity;
}
