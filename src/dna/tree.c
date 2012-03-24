/*
 * dna/tree.c
 *
 * Copyright 2012 Matthew Paiz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>

#include "function.h"
#include "tree.h"

struct _gk_tree {
  gk_tree **args;
  gk_function *f;
  float primitive;
};

gk_function *gk_tree_get_function(gk_tree *tree) {
  return tree->f;
}

gk_tree **gk_tree_get_args(gk_tree *tree) {
  return tree->args;
}

void gk_tree_node_assign(gk_tree *a, gk_tree *b) {
  *a = *b;
}

void gk_tree_set_primitive(gk_tree *tree, float primitive) {
  tree->primitive = primitive;
}

float gk_tree_get_primitive(gk_tree *tree) {
  return tree->primitive;
}

gk_tree *get_random_node(gk_function_pool *pool, int level, int maxlevel);

gk_tree *gk_tree_alloc_empty() {
  return (gk_tree *) malloc(sizeof(gk_tree));
}

gk_tree *gk_tree_alloc(gk_function *function) {
  int c;

  gk_tree *output = (gk_tree *) malloc(sizeof(gk_tree));
  output->f = function;
  output->args = (gk_function_get_arg_count(function)) ? (gk_tree **) malloc(gk_function_get_arg_count(function) * sizeof(gk_tree *)) : NULL;

  for(c = 0; c < gk_function_get_arg_count(function); c++)
    output->args[c] = NULL;

  output->primitive = 0;

  return output;
}

void gk_tree_append_random(gk_tree *node, gk_function_pool *pool, int level, int maxlevel) {
  int c;

  for(c = 0; c < gk_function_get_arg_count(node->f); c++) {
    if(!node->args[c]) {
      node->args[c] = get_random_node(pool, level + 1, maxlevel);
      gk_tree_append_random(node->args[c], pool, level + 1, maxlevel);
    }
  }
}

gk_tree *get_random_node(gk_function_pool *pool, int level, int maxlevel) {
  gk_tree *node;

  if(level < maxlevel) {
    node = gk_tree_alloc(gk_function_pool_get_random_function(pool));
  } else {

    int count = gk_function_pool_count_leaves(pool);

    node = gk_tree_alloc(gk_function_pool_get_leaf(RAND(count), pool));
  }
  node->primitive = RAND(9) + 1;
  return node;
}

gk_tree *gk_tree_clone(gk_tree *node) {

  gk_tree *copy = gk_tree_alloc(node->f);
  int c;

  for(c = 0; c < gk_function_get_arg_count(copy->f); c++) {
    copy->args[c] = gk_tree_clone(node->args[c]);
  }

  copy->primitive = node->primitive;

  return copy;
}

int gk_tree_realloc(gk_tree *output, gk_function *function) {
  int c;
  int original = gk_function_get_arg_count(output->f);

  for(c = 0; c < (gk_function_get_arg_count(output->f) - gk_function_get_arg_count(function)); c++)
    gk_tree_free(output->args[c + gk_function_get_arg_count(function)]);

  output->f = function;

  if(!gk_function_get_arg_count(function)) free(output->args); 
  output->args = (gk_function_get_arg_count(function)) ? (gk_tree **) realloc(output->args, gk_function_get_arg_count(function) * sizeof(gk_tree *)) : NULL;

  for(c = original; c < gk_function_get_arg_count(function); c++)
    output->args[c] = NULL;

  return 0;

}

void gk_tree_free(gk_tree *node) {
  int c;
  if(node && node->args) {
    for(c = 0; c < gk_function_get_arg_count(node->f); c++)
      gk_tree_free(node->args[c]);
  }

  free(node->args);
  free(node);
}

gk_tree *gk_tree_get_leaf(gk_tree *root, int *index) {

  int c;
  gk_tree *result;

  if(gk_function_get_arg_count(root->f) == 0) {
    if(*index == 0) return root;
    --(*index);
  }

  for(c = 0; c < gk_function_get_arg_count(root->f); c++) {
    if((result = gk_tree_get_leaf(root->args[c], index)))
        return result;
  }

  return NULL;

}

//TODO: temporary until parent pointer is used
gk_tree *gk_tree_get_node_and_parent(gk_tree *root, int *index, gk_tree **parent) {
  int c;
  gk_tree *result;

  if(*index == 0) return root;

  for(c = 0; c < gk_function_get_arg_count(root->f); c++) {
    --(*index);
    if((result = gk_tree_get_node_and_parent(root->args[c], index, parent))) {
      if(!*parent) *parent = root; 
      return result;
    }
  }

  return NULL;
}

gk_tree *gk_tree_get_node(gk_tree *root, int *index) {

  int c;
  gk_tree *result;

  if(*index == 0) return root;

  for(c = 0; c < gk_function_get_arg_count(root->f); c++) {
    --(*index);
    if((result = gk_tree_get_node(root->args[c], index)))
        return result;
  }

  return NULL;
}

int gk_tree_get_size(gk_tree *node) {

  int sum = 1;
  int c;

  for(c = 0; c < gk_function_get_arg_count(node->f); c++)
    sum += gk_tree_get_size(node->args[c]);  

  return sum;
}

int count_leafs(gk_tree *node) {
  int sum = 0;
  int c;

  if(!node->args)
    return 1;

  for(c = 0; c < gk_function_get_arg_count(node->f); c++)
    sum += count_leafs(node->args[c]);

  return sum;
}

int gk_tree_get_max_level(gk_tree *root) {

  int c, leaf_count = count_leafs(root);
  int b;

  int current, max = 0;

  for(c = 0; c < leaf_count; c++) {
    b = c;
    if((current = gk_tree_get_level(root, gk_tree_get_leaf(root, &b))) > max)
      max = current;
  }

  return max;

}

//TODO: Find More Efficient Way to Keep Track of This
int gk_tree_get_level(gk_tree *root, gk_tree *node) {

  int c, level;

  if(root == node)
    return 0;

  for(c = 0; c < gk_function_get_arg_count(root->f); c++) {
    if((level = gk_tree_get_level(root->args[c], node)) != -1) return 1 + level;
  }

  return -1;
}

float gk_tree_evaluate(gk_tree *value) {

  int c;
  float *arguments = (gk_function_get_arg_count(value->f) > 0) ? (float *) malloc(sizeof(float) * gk_function_get_arg_count(value->f)) : NULL;
  float result;

  for(c = 0; c < gk_function_get_arg_count(value->f); c++) {
    arguments[c] =gk_tree_evaluate((gk_tree *) value->args[c]);
  }

  if(gk_function_get_label(value->f)[0] != '#')
    result = (gk_function_invoke(value->f))(arguments);
  else
    result = (gk_function_invoke(value->f))(&value->primitive);

  free(arguments);

  return result;
}
