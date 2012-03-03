#ifndef __TREE_H__
#define __TREE_H__

#include "function.h"

struct _tree;
typedef struct _tree tree;

struct _tree {
  tree **args;
  function *f;
  float primitive;
};

tree *alloc_tree(function *function);
int realloc_tree(tree *output, function *function);
void free_tree(tree *node);
tree *copy_tree(tree *node);

int get_max_level(tree *root);


tree *get_leaf(tree *root, int *index);
int get_level(tree *root, tree *node);

float evaluate(tree *value);
tree *get_node(tree *, int *);
tree *get_node_and_parent(tree* root, int *index, tree**parent);
int get_size(tree *node);

#endif
