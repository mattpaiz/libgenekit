#ifndef __TREE_H__
#define __TREE_H__

#include "genekit.h"

struct _tree;
typedef struct _tree tree;

struct _tree {
  tree **args;
  gk_function *f;
  float primitive;
};

tree *alloc_tree(gk_function *function);
int realloc_tree(tree *output, gk_function *function);
void free_tree(tree *node);
tree *copy_tree(tree *node);

int get_max_level(tree *root);


tree *get_leaf(tree *root, int *index);
int get_level(tree *root, tree *node);

float evaluate(tree *value);
tree *get_node(tree *, int *);
tree *get_node_and_parent(tree* root, int *index, tree**parent);
int get_size(tree *node);
void append_random_node(tree *node, gk_function_pool pool, int level, int maxlevel);

#endif
