#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "mutate.h"
#include "rand.h"

#include "simulation.h"



void gk_set_population_size(gk_simulation *sim, int population_size) {
  sim->population_size = population_size;
}

void gk_set_max_depth(gk_simulation *sim, int max_depth) {
  sim->max_depth = max_depth;
}

void default_logger(gk_population *population, int generation) {
  int i;

  printf("Generation %d: ",  generation);

  for(i = 0; i < population->size; i++) {
    char *equation = gk_to_string(population->individuals[i]);
    printf("%s ", equation);
    free(equation);
  }
  printf("\n");
}

gk_simulation *gk_create_simulation() {
  gk_simulation *sim = (gk_simulation *) malloc(sizeof(gk_simulation)); 

  sim->log_generation = &default_logger;

  return sim;
}

void gk_set_function_pool(gk_simulation *sim, function *functions, int n) {
  sim->pool.functions = functions;
  sim->pool.function_count = n;
}


chromosome *gk_alloc_chromosome(gk_simulation *simulation) { 

  chromosome *c = (chromosome *) malloc(sizeof(chromosome)); 
  c->pool = &simulation->pool;
  c->node = NULL;

  return c;
}

