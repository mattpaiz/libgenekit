#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "simulation.h"
#include "function.h"
#include "chromosome.h"
#include "mutate.h"

struct _gk_population {
  gk_chromosome **individuals;
  int size;
  float max_fitness;
  float total_fitness;
  int max_index;
};

struct _gk_chromosome {
  gk_tree *node;
  gk_function_pool *pool;
  float fitness;
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

  float fitness = population->individuals[index]->fitness;
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

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {
   crossover(&a->node, &b->node, max_depth);
}

gk_chromosome *gk_population_get_individual(gk_population *population, int index) {
  return population->individuals[index];
}

void gk_population_alloc_individual(gk_population *population, gk_simulation *simulation, int index) {
   population->individuals[index] = gk_alloc_chromosome(simulation);
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

void gk_chromosome_set_fitness(gk_chromosome *c, float fitness) {
  c->fitness = fitness;
}

float gk_chromosome_get_fitness(gk_chromosome *c) {
  return c->fitness;
}

void gk_randomize_chromosome(gk_chromosome *c, int depth) {
   if(c->node) free_tree(c->node);
   c->node = alloc_tree(get_branch_function(RAND(count_branch_functions(c->pool)), c->pool));
   append_random_node(c->node, c->pool, 0, depth);
}

gk_chromosome *gk_clone_chromosome(gk_chromosome *c) {
  gk_chromosome *clone = (gk_chromosome *) malloc(sizeof(gk_chromosome));
  clone->fitness = c->fitness;
  clone->node = copy_tree(c->node);
  clone->pool = c->pool;

  return clone;
}

void gk_free_chromosome(gk_chromosome *c) {
  if(c->node) free_tree(c->node);
  free(c);
}

void gk_clear_population(gk_population *c) {
  int i;
  for(i = 0; i < c->size; i++) {
    gk_free_chromosome(c->individuals[i]);
  }
}

void gk_free_population(gk_population *c) {
  gk_clear_population(c);
  free(c);
}

int set_chromosome_node(gk_chromosome *c, gk_tree *node) {
  c->node = node;
  return 0;
}

void gk_set_equation(gk_chromosome *c, char *equation) {
  c->node = convert_to_tree(equation, c->pool);
}

char *gk_to_string(gk_chromosome *c) {
  return convert_to_hr_equation(c->node); 
}


gk_chromosome *gk_alloc_chromosome(gk_simulation *sim) { 

  gk_chromosome *c = (gk_chromosome *) malloc(sizeof(gk_chromosome)); 
  c->pool = gk_simulation_get_function_pool(sim);
  c->node = NULL;

  return c;
}
