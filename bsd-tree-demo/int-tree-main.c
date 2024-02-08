// int_tree_main.c - Demonstrates how to use RB Tree from BSD

#include "int-tree.h"
#include <stdio.h>

int main() {
    struct int_tree tree;
    int_tree_init(&tree);

    // Insert values
    int_tree_insert(&tree, 5);
    int_tree_insert(&tree, 3);
    int_tree_insert(&tree, 10);

    // Find and print a value

    for (int value=0; value <= 10; value++) {
       int_tree_node_t *found = int_tree_find(&tree, value);
       if (found) {
           printf("Found: %d\n", found->value);
       } else {
           printf("Not found: %d\n", value);
       }
    }

    // Cleanup and other operations...

    return 0;
}

