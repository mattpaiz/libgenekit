/*
 * chromosome.c
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

#include "DNA/tree.h"
#include "equation.h"
#include "simulation.h"
#include "function.h"
#include "chromosome.h"
#include "mutate.h"

struct _gk_chromosome {
  gk_tree *node;
  gk_function_pool *pool;
  float fitness;
};

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {
   gk_mutate_crossover(&a->node, &b->node, max_depth);
}

void gk_chromosome_set_fitness(gk_chromosome *c, float fitness) {
  c->fitness = fitness;
}

float gk_chromosome_get_fitness(gk_chromosome *c) {
  return c->fitness;
}

void gk_chromosome_randomize(gk_chromosome *c, int depth) {
   if(c->node) gk_tree_free(c->node);
   c->node = gk_tree_alloc(gk_function_pool_get_branch(RAND(gk_function_pool_count_branches(c->pool)), c->pool));
   gk_tree_append_random(c->node, c->pool, 0, depth);
}

gk_chromosome *gk_chromosome_clone(gk_chromosome *c) {
  gk_chromosome *clone = (gk_chromosome *) malloc(sizeof(gk_chromosome));
  clone->fitness = c->fitness;
  clone->node = gk_tree_clone(c->node);
  clone->pool = c->pool;

  return clone;
}

void gk_chromosome_free(gk_chromosome *c) {
  if(c->node) gk_tree_free(c->node);
  free(c);
}

float gk_chromosome_evaluate(gk_chromosome *c) {
  return gk_tree_evaluate(c->node);  
}


int gk_chromosome_set_node(gk_chromosome *c, gk_tree *node) {
  c->node = node;
  return 0;
}

void gk_chromosome_set_equation(gk_chromosome *c, char *equation) {
  c->node = gk_equation_convert(equation, c->pool);
}

char *gk_chromosome_to_string_full(gk_chromosome *c) {
  return gk_equation_alloc(c->node);
}

char *gk_chromosome_to_string(gk_chromosome *c) {
  return gk_equation_alloc_hr(c->node); 
}


gk_chromosome *gk_chromosome_alloc(gk_simulation *sim) { 

  gk_chromosome *c = (gk_chromosome *) malloc(sizeof(gk_chromosome)); 
  c->pool = gk_simulation_get_function_pool(sim);
  c->node = NULL;

  return c;
}
