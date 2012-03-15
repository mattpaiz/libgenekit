/*
 * simulation.h
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

#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "genekit.h"

typedef float(*gk_fitness_function)(gk_chromosome *);
typedef void(*gk_log_function)(gk_population *, int);

gk_fitness_function gk_simulation_fitness(gk_simulation *);
gk_log_function gk_simulation_log(gk_simulation *);

void gk_simulation_set_population_size(gk_simulation *, int);
void gk_simulation_set_max_depth(gk_simulation *, int);
void gk_simulation_set_function_pool(gk_simulation *, gk_function_pool *);
void gk_simulation_set_fitness(gk_simulation *, gk_fitness_function);

int gk_simulation_get_population_size(gk_simulation *);
int gk_simulation_get_max_depth(gk_simulation *);
gk_function_pool *gk_simulation_get_function_pool(gk_simulation *);

gk_simulation *gk_simulation_alloc();
void gk_simulation_free(gk_simulation *);

#endif
