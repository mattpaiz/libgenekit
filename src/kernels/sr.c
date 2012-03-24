/*
 * kernels/sr.c
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
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "population.h"
#include "simulation.h"
#include "chromosome.h"
#include "bare.h"
#include "kernel.h"
#include "mutate.h"
#include "function.h"
#include "equation.h"
#include "dna/tree.h"

void _gk_sr_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {

  void *dna_a = gk_chromosome_get_dna(a);
  void *dna_b = gk_chromosome_get_dna(b);

  gk_mutate_crossover(dna_a, dna_b, max_depth);
}

void _gk_sr_randomize(gk_chromosome *c, int depth) {

  void *dna_c = *gk_chromosome_get_dna(c);
  gk_function_pool *pool = gk_chromosome_get_pool(c);

  if(dna_c) gk_tree_free(dna_c);
  gk_chromosome_set_dna(c, gk_tree_alloc(gk_function_pool_get_branch(RAND(gk_function_pool_count_branches(pool)), pool)));

  gk_tree_append_random(*gk_chromosome_get_dna(c), pool, 0, depth);
}

char *_gk_sr_to_string(gk_chromosome *c) {
  return gk_equation_alloc_hr(*gk_chromosome_get_dna(c)); 
}

void *_gk_sr_clone(void *dna) {
  return gk_tree_clone(dna);
}

float _gk_sr_evaluate(void *dna) {
  return gk_tree_evaluate(dna);
}

void _gk_sr_free(void *dna) {
  gk_tree_free(dna);
}

gk_kernel *gk_create_sr_kernel() {

  gk_kernel *sr_kernel = gk_create_bare_kernel();

  sr_kernel->bindings[GK_KERNEL_BINDING_CROSSOVER] = &_gk_sr_crossover;
  sr_kernel->bindings[GK_KERNEL_BINDING_RANDOMIZE] = &_gk_sr_randomize;
  sr_kernel->bindings[GK_KERNEL_BINDING_DISPLAY] = &_gk_sr_to_string;
  sr_kernel->bindings[GK_KERNEL_BINDING_CLONE] = &_gk_sr_clone;
  sr_kernel->bindings[GK_KERNEL_BINDING_FREE] = &_gk_sr_free;
  sr_kernel->bindings[GK_KERNEL_BINDING_EVALUATE] = &_gk_sr_evaluate;

  return sr_kernel;
}
