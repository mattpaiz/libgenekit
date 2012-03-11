#include <stdlib.h>

#include "function.h"
#include "tree.h"

tree *get_random_node(function_pool pool, int level, int maxlevel);

tree *alloc_tree(gk_function *function) {
  int c;

  tree *output = (tree *) malloc(sizeof(tree));
  output->f = function;
  output->args = (function->arg_count) ? (tree **) malloc(function->arg_count * sizeof(tree *)) : NULL;

  for(c = 0; c < function->arg_count; c++)
    output->args[c] = NULL;

  output->primitive = 0;

  return output;
}

void append_random_node(tree *node, function_pool pool, int level, int maxlevel) {
  int c;

  for(c = 0; c < node->f->arg_count; c++) {
    if(!node->args[c]) {
      node->args[c] = get_random_node(pool, level + 1, maxlevel);
      append_random_node(node->args[c], pool, level + 1, maxlevel);
    }
  }
}

tree *get_random_node(function_pool pool, int level, int maxlevel) {
  tree *node;

  if(level < maxlevel)
    return alloc_tree(&pool.functions[RAND(pool.function_count)]);
  else {

    int count = count_leaf_functions(pool);

    node = alloc_tree(get_leaf_function(RAND(count), pool));
    node->primitive = RAND(9) + 1;
    return node;
  }
}

tree *copy_tree(tree *node) {

  tree *copy = alloc_tree(node->f);
  int c;

  for(c = 0; c < copy->f->arg_count; c++) {
    copy->args[c] = copy_tree(node->args[c]);
  }

  copy->primitive = node->primitive;

  return copy;
}

int realloc_tree(tree *output, gk_function *function) {
  int c;
  int original = output->f->arg_count;

  for(c = 0; c < (output->f->arg_count - function->arg_count); c++)
    free_tree(output->args[c + function->arg_count]);

  output->f = function;

  if(!function->arg_count) free(output->args); 
  output->args = (function->arg_count) ? (tree **) realloc(output->args, function->arg_count * sizeof(tree *)) : NULL;

  for(c = original; c < function->arg_count; c++)
    output->args[c] = NULL;

  return 0;

}

void free_tree(tree *node) {
  int c;
  if(node && node->args) {
    for(c = 0; c < node->f->arg_count; c++)
      free_tree(node->args[c]);
  }

  free(node->args);
  free(node);
}

tree *get_leaf(tree *root, int *index) {

  int c;
  tree *result;

  if(root->f->arg_count == 0) {
    if(*index == 0) return root;
    --(*index);
  }

  for(c = 0; c < root->f->arg_count; c++) {
    if((result = get_leaf(root->args[c], index)))
        return result;
  }

  return NULL;

}

//TODO: temporary until parent pointer is used
tree *get_node_and_parent(tree* root, int *index, tree** parent) {
  int c;
  tree *result;

  if(*index == 0) return root;

  for(c = 0; c < root->f->arg_count; c++) {
    --(*index);
    if((result = get_node_and_parent(root->args[c], index, parent))) {
      if(!*parent) *parent = root; 
      return result;
    }
  }

  return NULL;
}

tree *get_node(tree* root, int *index) {

  int c;
  tree *result;

  if(*index == 0) return root;

  for(c = 0; c < root->f->arg_count; c++) {
    --(*index);
    if((result = get_node(root->args[c], index)))
        return result;
  }

  return NULL;
}

int get_size(tree *node) {

  int sum = 1;
  int c;

  for(c = 0; c < node->f->arg_count; c++)
    sum += get_size(node->args[c]);  

  return sum;
}

int count_leafs(tree *node) {
  int sum = 0;
  int c;

  if(!node->args)
    return 1;

  for(c = 0; c < node->f->arg_count; c++)
    sum += count_leafs(node->args[c]);

  return sum;
}

int get_max_level(tree *root) {

  int c, leaf_count = count_leafs(root);
  int b;

  int current, max = 0;

  for(c = 0; c < leaf_count; c++) {
    b = c;
    if((current = get_level(root, get_leaf(root, &b))) > max)
      max = current;
  }

  return max;

}

//TODO: Find More Efficient Way to Keep Track of This
int get_level(tree *root, tree *node) {

  int c, level;

  if(root == node)
    return 0;

  for(c = 0; c < root->f->arg_count; c++) {
    if((level = get_level(root->args[c], node)) != -1) return 1 + level;
  }

  return -1;
}

float evaluate(tree *value) {

  int c;
  float *arguments = (value->f->arg_count > 0) ? (float *) malloc(sizeof(float) * value->f->arg_count) : NULL;
  float result;

  for(c = 0; c < value->f->arg_count; c++) {
    arguments[c] = evaluate((tree *) value->args[c]);
  }

  if(value->f->label[0] != '#')
    result = (value->f->ptr)(arguments);
  else
    result = (value->f->ptr)(&value->primitive);

  free(arguments);

  return result;
}
