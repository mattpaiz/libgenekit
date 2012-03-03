#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "mutate.h"
#include "rand.h"

#include "simulation.h"

#define STALE_LIMIT 100 

#define ERPA_LIMIT 8 
#define ERPA_START 4

#define MAX_POPULATION 100

#define HUMAN_READABLE 1

#define PROXIMITY 0.0001

tree *get_random_node(function_pool *pool, int args, int level, int maxlevel);

float highest_fitness;

float fitness(tree *node) {
  return 0;
}

function *get_leaf_function(int index, function_pool *pool) {

  int c;
  for(c = 0; c < pool->function_count; c++) {
    if(pool->functions[c].arg_count == 0) {
      if(index-- == 0)
        return &pool->functions[c];
    }
  }

  return NULL;
}

int count_leaf_functions(function_pool *pool) {
  int c, sum = 0;

  for(c = 0; c < pool->function_count; c++)
    if(pool->functions[c].arg_count == 0)
      sum++;

  return sum;
}

void append_random_node(tree *node, function_pool *pool, int level, int maxlevel) {
  int c;

  for(c = 0; c < node->f->arg_count; c++) {
    if(!node->args[c]) {
      node->args[c] = get_random_node(pool, 0, level + 1, maxlevel);
      append_random_node(node->args[c], pool, level + 1, maxlevel);
    }
  }
}

tree *get_random_node(function_pool *pool, int args, int level, int maxlevel) {
  tree *node;

  if(level < maxlevel)
    return alloc_tree(&pool->functions[RAND(pool->function_count)]);
  else {

    int count = count_leaf_functions(pool);

    node = alloc_tree(get_leaf_function(RAND(count), pool));
    node->primitive = RAND(10000);
    return node;
  }
}


int compare_rev(const void *a, const void *b) {

  tree **tree_a = (tree **) a;
  tree **tree_b = (tree **) b;

  int size;

  if(fabs((*tree_a)->score - (*tree_b)->score)  < PROXIMITY) {
    if((size = get_size(*tree_a) - get_size(*tree_b)) != 0) 
      return size;
  } 
  
  if((*tree_a)->score > (*tree_b)->score)
    return -1;
  else
    return 1;
}

tree *genekit_select_individual(tree **population, int population_size, float total_fitness) {

  float probability = FRAND();
  float prob_sum = 0;

  int c = 0;

  while((c < population_size) && (prob_sum += (population[c++]->score / total_fitness)) < probability);

  return population[c - 1];
}

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

