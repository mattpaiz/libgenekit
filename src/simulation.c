/*
 * simulation.c
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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "equation.h"

#include "chromosome.h"
#include "population.h"
#include "simulation.h"

struct _gk_simulation {
  int population_size;
  int max_depth;
  int max_generations;

  gk_log_function log;
  gk_fitness_function fitness;
};

gk_log_function gk_simulation_log(gk_simulation *sim) {
  return sim->log;
}

gk_fitness_function gk_simulation_fitness(gk_simulation *sim) {
  return sim->fitness;
}

void gk_simulation_set_fitness(gk_simulation *sim, gk_fitness_function f) {
  sim->fitness = f;
}

int gk_simulation_get_population_size(gk_simulation *sim) {
  return sim->population_size;
}

int gk_simulation_get_max_depth(gk_simulation *sim) {
  return sim->max_depth;
}

int gk_simulation_get_max_generations(gk_simulation *sim) {
  return sim->max_generations;
}

void gk_simulation_set_max_generations(gk_simulation *sim, int max_generations) {
  sim->max_generations = max_generations;
}

void gk_simulation_set_population_size(gk_simulation *sim, int population_size) {
  sim->population_size = population_size;
}

void gk_simulation_set_max_depth(gk_simulation *sim, int max_depth) {
  sim->max_depth = max_depth;
}

void default_logger(gk_population *population, int generation) {

  printf("Generation %d [%f]: ",  generation, gk_population_get_max_fitness(population));

  char *equation = gk_chromosome_to_string(gk_population_get_individual(population, gk_population_get_max_index(population)));
  printf("%s = %f", equation, gk_chromosome_evaluate(gk_population_get_most_fit_individual(population)));
  free(equation);
 
  printf("\n");
}

gk_simulation *gk_simulation_alloc() {
  gk_simulation *sim = (gk_simulation *) malloc(sizeof(gk_simulation)); 

  sim->log = &default_logger;

  return sim;
}

void gk_simulation_free(gk_simulation *simulation) {
  free(simulation);
}



