/*
 * kernel.c
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

#include "population.h"
#include "chromosome.h"
#include "simulation.h"
#include "kernel.h"

void *gk_kernel_get_binding(gk_kernel *kernel, int binding) {
  return kernel->bindings[binding];
}

int gk_kernel_start(gk_kernel *kernel, gk_simulation *sim) {

  int i, generation = 0;
  float fitness;

  gk_population *population, *new_population;
  gk_chromosome *individual;
  population = gk_population_alloc(gk_simulation_get_population_size(sim));

  kernel->init(sim);
  kernel->populate(kernel, sim, population);

  while(!kernel->terminate(sim, population, generation)) {

    gk_population_reset_max_values(population);

    for(i = 0; i < gk_population_get_size(population); i++) {
      individual = gk_population_get_individual(population, i);
      if(!generation || i < gk_population_get_size(population) / 4) {
        fitness = gk_simulation_fitness(sim)(individual);
        gk_chromosome_set_fitness(individual, fitness);
      }
      gk_population_register_fitness(population, i);
    }
    gk_simulation_log(sim)(population, generation);

    new_population = kernel->process(sim, population);
    gk_population_free(population);
    population = new_population;

    generation++;
  }

  kernel->cleanup(sim, population);
  gk_population_clear(population);

  return 0;
}

gk_function_pool *gk_kernel_get_function_pool(gk_kernel *kernel) {
  return kernel->pool;
}

void gk_kernel_set_function_pool(gk_kernel *kernel, gk_function_pool *pool) {
  kernel->pool = pool;
}
