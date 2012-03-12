#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "mutate.h"

#include "chromosome.h"
#include "simulation.h"

struct _gk_simulation {
  int population_size;
  int max_depth;
  gk_function_pool *pool;

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

gk_function_pool *gk_simulation_get_function_pool(gk_simulation *sim) {
  return sim->pool;
}

void gk_simulation_set_population_size(gk_simulation *sim, int population_size) {
  sim->population_size = population_size;
}

void gk_simulation_set_max_depth(gk_simulation *sim, int max_depth) {
  sim->max_depth = max_depth;
}

void default_logger(gk_population *population, int generation) {

  printf("Generation %d [%f]: ",  generation, gk_population_get_max_fitness(population));

  char *equation = gk_to_string(gk_population_get_individual(population, gk_population_get_max_index(population)));
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

void gk_simulation_set_function_pool(gk_simulation *sim, gk_function_pool *pool) {
  sim->pool = pool;
}



