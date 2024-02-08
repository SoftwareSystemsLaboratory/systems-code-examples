// int_tree.c
//
#include "int-tree.h"
#include <stdlib.h>

int int_tree_node_cmp(int_tree_node_t *a, int_tree_node_t *b) {
    return (a->value < b->value) ? -1 : (a->value > b->value);
}

RB_GENERATE(int_tree, int_tree_node, entry, int_tree_node_cmp);

void int_tree_init(struct int_tree *tree) {
    RB_INIT(tree);
}

void int_tree_insert(struct int_tree *tree, int value) {
    int_tree_node_t *node = malloc(sizeof(int_tree_node_t));
    if (node) {
        node->value = value;
        if (RB_INSERT(int_tree, tree, node)) {
            // Handle insertion error (e.g., value already exists)
            free(node);
        }
    }
}

int_tree_node_t *int_tree_find(struct int_tree *tree, int value) {
    int_tree_node_t node;
    node.value = value;
    return RB_FIND(int_tree, tree, &node);
}

void int_tree_remove(struct int_tree *tree, int_tree_node_t *node) {
    if (node) {
        RB_REMOVE(int_tree, tree, node);
        free(node);
    }
}

