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
#include "kernel.h"
#include "function.h"
#include "chromosome.h"
#include "mutate.h"

struct _gk_chromosome {
  void *dna;
  gk_function_pool *pool;
  float fitness;

  void *(*_clone)(void *dna);
  void (*_free)(void *dna);
  void (*_crossover)(gk_chromosome *, gk_chromosome *, int);
  void (*_randomize)(gk_chromosome *, int);
  float (*_evaluate)(void *);
  char *(*_to_string)(gk_chromosome *);
};

void **gk_chromosome_get_dna(gk_chromosome *chromosome) {
  return &chromosome->dna;
}

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {
  a->_crossover(a, b, max_depth);
}

void gk_chromosome_set_fitness(gk_chromosome *c, float fitness) {
  c->fitness = fitness;
}

float gk_chromosome_get_fitness(gk_chromosome *c) {
  return c->fitness;
}

void gk_chromosome_randomize(gk_chromosome *c, int depth) {
  c->_randomize(c, depth);
}

gk_chromosome *gk_chromosome_clone(gk_chromosome *c) {
  gk_chromosome *clone = (gk_chromosome *) malloc(sizeof(gk_chromosome));
  clone->fitness = c->fitness;
  clone->dna = c->_clone(c->dna);
  clone->pool = c->pool;
  clone->_crossover = c->_crossover;
  clone->_randomize = c->_randomize;
  clone->_to_string = c->_to_string;
  clone->_clone = c->_clone;
  clone->_free = c->_free;
  clone->_evaluate = c->_evaluate;

  return clone;
}

void gk_chromosome_free(gk_chromosome *c) {
  if(c->dna) c->_free(c->dna);
  free(c);
}

float gk_chromosome_evaluate(gk_chromosome *c) {
  return c->_evaluate(c->dna);  
}


void gk_chromosome_set_dna(gk_chromosome *c, void *dna) {
  c->dna = dna;
}

void gk_chromosome_set_equation(gk_chromosome *c, char *equation) {
  c->dna = gk_equation_convert(equation, c->pool);
}

char *gk_chromosome_to_string(gk_chromosome *c) {
  return c->_to_string(c);
}

gk_function_pool *gk_chromosome_get_pool(gk_chromosome *chromosome) {
  return chromosome->pool;
}

gk_chromosome *gk_chromosome_alloc(gk_kernel *kernel) { 
  gk_chromosome *c = (gk_chromosome *) malloc(sizeof(gk_chromosome)); 
  c->pool = gk_kernel_get_function_pool(kernel);
  c->_crossover = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_CROSSOVER);
  c->_randomize = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_RANDOMIZE);
  c->_to_string = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_DISPLAY);
  c->_clone = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_CLONE);
  c->_free = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_FREE);
  c->_evaluate = gk_kernel_get_binding(kernel, GK_KERNEL_BINDING_EVALUATE);
  c->dna = NULL;

  return c;
}
