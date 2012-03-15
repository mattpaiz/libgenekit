/*
 * population.h
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

#ifndef __POPULATION_H__
#define __POPULATION_H__

#include "genekit.h"

gk_population *gk_population_alloc(int);
gk_chromosome *gk_population_get_individual(gk_population *, int);
gk_chromosome *gk_population_get_most_fit_individual(gk_population *population);
gk_chromosome *gk_population_select(gk_population *population);
void gk_population_alloc_individual(gk_population *population, gk_simulation *simulation, int index);
void gk_population_reset_max_values(gk_population *);
int gk_population_get_size(gk_population *);
float gk_population_get_total_fitness(gk_population *);
int gk_population_get_max_index(gk_population *);
float gk_population_get_max_fitness(gk_population *);
void gk_population_set_individual(gk_population *population, int index, gk_chromosome *c);
void gk_population_register_fitness(gk_population *, int);
void gk_population_free(gk_population *c);
void gk_population_clear(gk_population *);


#endif
