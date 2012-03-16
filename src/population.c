/*
 * population.c
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
#include "chromosome.h"
#include "population.h"

struct _gk_population {
  gk_chromosome **individuals;
  int size;
  float max_fitness;
  float total_fitness;
  int max_index;
};

void gk_population_set_individual(gk_population *population, int index, gk_chromosome *c) {
  population->individuals[index] = c;
}

float gk_population_get_max_fitness(gk_population *population) {
  return population->max_fitness;
}

int gk_population_get_max_index(gk_population *population) {
  return population->max_index;
}

float gk_population_get_total_fitness(gk_population *population) {
  return population->total_fitness;
}

int gk_population_get_size(gk_population *population) {
  return population->size;
}

void gk_population_register_fitness(gk_population *population, int index) {

  float fitness = gk_chromosome_get_fitness(population->individuals[index]);
  population->total_fitness += fitness;
  if(fitness > population->max_fitness) {
    population->max_index = index;
    population->max_fitness = fitness;
  }
}

void gk_population_reset_max_values(gk_population *population) {
  population->max_fitness = 0;
  population->total_fitness = 0;
  population->max_index = 0;
}

gk_chromosome *gk_population_get_individual(gk_population *population, int index) {
  return population->individuals[index];
}

void gk_population_alloc_individual(gk_population *population, gk_kernel *kernel, int index) {
   population->individuals[index] = gk_chromosome_alloc(kernel);
}

gk_population *gk_population_alloc(int population_size) {

  gk_population *population = (gk_population *) malloc(sizeof(gk_population));
  population->individuals = (gk_chromosome **) malloc(sizeof(gk_chromosome *) * population_size);
  population->size = population_size;
  population->max_fitness = 0;
  population->total_fitness = 0;
  population->max_index = 0;

  return population;
}

gk_chromosome *gk_population_get_most_fit_individual(gk_population *population) {
  return population->individuals[population->max_index];
}

void gk_population_clear(gk_population *c) {
  int i;
  for(i = 0; i < c->size; i++) {
    gk_chromosome_free(c->individuals[i]);
  }
}

void gk_population_free(gk_population *c) {
  gk_population_clear(c);
  free(c);
}

gk_chromosome *gk_population_select(gk_population *population) {
  float random = FRAND();
  float sum = 0;

  int c = 0;

  while((c < gk_population_get_size(population)) && (sum += (gk_chromosome_get_fitness(gk_population_get_individual(population, c++)) / gk_population_get_total_fitness(population))) < random);

  return gk_population_get_individual(population, c - 1);
}
