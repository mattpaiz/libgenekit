/*
 * dna/tree.h
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

#ifndef __TREE_H__
#define __TREE_H__

#include "../genekit.h"

gk_tree *gk_tree_alloc(gk_function *function);
int gk_tree_realloc(gk_tree *output, gk_function *function);
void gk_tree_free(gk_tree *node);
gk_tree *gk_tree_clone(gk_tree *node);

gk_tree *gk_tree_alloc_empty();
void gk_tree_node_assign(gk_tree *a, gk_tree *b);

void gk_tree_set_primitive(gk_tree *tree, float primitive);

int gk_tree_get_max_level(gk_tree *root);
gk_function *gk_tree_get_function(gk_tree *);
float gk_tree_get_primitive(gk_tree *);
gk_tree **gk_tree_get_args(gk_tree *);

gk_tree *gk_tree_get_leaf(gk_tree *root, int *index);
int gk_tree_get_level(gk_tree *root, gk_tree *node);

float gk_tree_evaluate(gk_tree *value);
gk_tree *gk_tree_get_node(gk_tree *, int *);
gk_tree *gk_tree_get_node_and_parent(gk_tree *root, int *index, gk_tree **parent);
int gk_tree_get_size(gk_tree *node);
void gk_tree_append_random(gk_tree *node, gk_function_pool *pool, int level, int maxlevel);
void gk_tree_crossover(gk_tree **male, gk_tree **female, int level);
void gk_tree_mutate(gk_tree *input, gk_function_pool *pool, int max_level);

#endif
