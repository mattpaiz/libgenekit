/*
 * chromosome.h
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

#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "genekit.h"

gk_chromosome *gk_chromosome_alloc(gk_kernel *kernel);
gk_chromosome *gk_chromosome_clone(gk_chromosome *c);
void gk_chromosome_free(gk_chromosome *c);

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth);
void gk_chromosome_randomize(gk_chromosome *c, int depth);
char *gk_chromosome_to_string(gk_chromosome *c);
float gk_chromosome_evaluate(gk_chromosome *c);

float gk_chromosome_get_fitness(gk_chromosome *);

void gk_chromosome_set_equation(gk_chromosome *, char *);
void gk_chromosome_set_fitness(gk_chromosome *c, float fitness);
void gk_chromosome_set_dna(gk_chromosome *c, void *);

#endif
