// int_tree.h
#ifndef INT_TREE_H
#define INT_TREE_H

#include "bsd-tree.h"

typedef struct int_tree_node {
    int value;
    RB_ENTRY(int_tree_node) entry;
} int_tree_node_t;

RB_HEAD(int_tree, int_tree_node);

void int_tree_init(struct int_tree *tree);
void int_tree_insert(struct int_tree *tree, int value);
int_tree_node_t *int_tree_find(struct int_tree *tree, int value);
void int_tree_remove(struct int_tree *tree, int_tree_node_t *node);
// Additional declarations for traversal or other operations can be added here

#endif // INT_TREE_H

