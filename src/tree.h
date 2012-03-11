#ifndef __TREE_H__
#define __TREE_H__

#include "genekit.h"

struct _gk_tree {
  gk_tree **args;
  gk_function *f;
  float primitive;
};

gk_tree *alloc_tree(gk_function *function);
int realloc_tree(gk_tree *output, gk_function *function);
void free_tree(gk_tree *node);
gk_tree *copy_tree(gk_tree *node);

int get_max_level(gk_tree *root);


gk_tree *get_leaf(gk_tree *root, int *index);
int get_level(gk_tree *root, gk_tree *node);

float evaluate(gk_tree *value);
gk_tree *get_node(gk_tree *, int *);
gk_tree *get_node_and_parent(gk_tree *root, int *index, gk_tree **parent);
int get_size(gk_tree *node);
void append_random_node(gk_tree *node, gk_function_pool *pool, int level, int maxlevel);

#endif
