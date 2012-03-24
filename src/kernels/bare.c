/*
 * kernels/bare.c
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
#include "function.h"
#include "equation.h"
#include "dna/tree.h"

int gk_bare_populate(gk_kernel *kernel, gk_simulation *sim, gk_population *population) {

 int i;

 for(i = 0; i < gk_simulation_get_population_size(sim); i++) {
   gk_population_alloc_individual(population, kernel, i);
   gk_chromosome_randomize(gk_population_get_individual(population, i), gk_simulation_get_max_depth(sim));
 }

 return 0; 
}

int gk_bare_terminate(gk_population *population, int generation) {
  return (generation >= 50000);
}

gk_population *gk_bare_process(gk_simulation *sim, gk_population *population) {

 gk_chromosome *male;
 gk_chromosome *female;

 int i;

 gk_population *new_population = gk_population_alloc(gk_population_get_size(population));

 for(i = 0; i < gk_population_get_size(population) / 4; i+=2) {
   male = gk_chromosome_clone(gk_population_select(population));
   female = gk_chromosome_clone(gk_population_select(population));

   if(RAND(4))
     gk_chromosome_crossover(male, female, gk_simulation_get_max_depth(sim));
   else {
     gk_chromosome_mutate(male, gk_simulation_get_max_depth(sim));
     gk_chromosome_mutate(female, gk_simulation_get_max_depth(sim));
   }

   gk_population_set_individual(new_population, i, male);
   gk_population_set_individual(new_population, i + 1, female);
 }

 for(i = gk_population_get_size(population) / 4; i < gk_population_get_size(population); i++) {
   gk_population_set_individual(new_population, i, gk_chromosome_clone(gk_population_select(population)));
 }

 gk_chromosome *best = gk_population_get_most_fit_individual(population);
 //gk_free_chromosome(individuals[gk_population_get_max_index(population)]);
 gk_population_set_individual(new_population, gk_population_get_max_index(population), gk_chromosome_clone(best));

 return new_population; 
}

int gk_bare_init(gk_simulation *sim) {
  srand(time(NULL));
  rand();

  return 0;
}

int gk_bare_cleanup(gk_simulation *sim, gk_population *population) {
  return 0;
}

gk_kernel *gk_create_bare_kernel() {

  gk_kernel *my_kernel = (gk_kernel *) malloc(sizeof(gk_kernel));
  my_kernel->init = &gk_bare_init;
  my_kernel->populate = &gk_bare_populate;
  my_kernel->process = &gk_bare_process;
  my_kernel->terminate = &gk_bare_terminate;
  my_kernel->cleanup = &gk_bare_cleanup;

  my_kernel->bindings = malloc(sizeof(void *) * GK_BINDING_COUNT);

  return my_kernel;
}
