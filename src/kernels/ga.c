/*
 * kernels/ga.c
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

#include "../kernel.h"
#include "bare.h"
#include "../chromosome.h"
#include "../dna/vector.h"
#include "ga.h"

void _gk_ga_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {

  void *dna_a = *gk_chromosome_get_dna(a);
  void *dna_b = *gk_chromosome_get_dna(b);

  gk_vector_mutate(dna_a);
  gk_vector_mutate(dna_b);
}

void _gk_ga_randomize(gk_chromosome *c, int depth) {
  CTYPE *dna = (CTYPE *) malloc(sizeof(CTYPE));
  *dna = RAND(GA_MAX - GA_MIN) + GA_MIN;
  gk_chromosome_set_dna(c, dna);
}

char *_gk_ga_to_string(gk_chromosome *c) {
  return gk_vector_display(*((CTYPE *)(*gk_chromosome_get_dna(c))));
}

void *_gk_ga_clone(void *dna) {
  CTYPE *clone = (CTYPE *) malloc(sizeof(CTYPE));
  *clone = *((CTYPE *)dna);
  return clone;
}

float _gk_ga_evaluate(void *dna) {
  return gk_vector_evaluate(*((CTYPE *)dna));
}

void _gk_ga_free(void *dna) {
  free(dna);
}

gk_kernel *gk_create_ga_kernel() {

  gk_kernel *ga_kernel = gk_create_bare_kernel();

  ga_kernel->bindings[GK_KERNEL_BINDING_CROSSOVER] = &_gk_ga_crossover;
  ga_kernel->bindings[GK_KERNEL_BINDING_RANDOMIZE] = &_gk_ga_randomize;
  ga_kernel->bindings[GK_KERNEL_BINDING_DISPLAY] = &_gk_ga_to_string;
  ga_kernel->bindings[GK_KERNEL_BINDING_CLONE] = &_gk_ga_clone;
  ga_kernel->bindings[GK_KERNEL_BINDING_FREE] = &_gk_ga_free;
  ga_kernel->bindings[GK_KERNEL_BINDING_EVALUATE] = &_gk_ga_evaluate;

  return ga_kernel;
}
