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

void gk_population_alloc_individual(gk_population *population, gk_simulation *simulation, int index) {
   population->individuals[index] = gk_chromosome_alloc(simulation);
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

void gk_clear_population(gk_population *c) {
  int i;
  for(i = 0; i < c->size; i++) {
    gk_chromosome_free(c->individuals[i]);
  }
}

void gk_free_population(gk_population *c) {
  gk_clear_population(c);
  free(c);
}
