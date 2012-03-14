#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "simulation.h"
#include "function.h"
#include "chromosome.h"
#include "mutate.h"

struct _gk_chromosome {
  gk_tree *node;
  gk_function_pool *pool;
  float fitness;
};


void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth) {
   crossover(&a->node, &b->node, max_depth);
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

float gk_chromosome_evaluate(gk_chromosome *c) {
  return evaluate(c->node);  
}


int set_chromosome_node(gk_chromosome *c, gk_tree *node) {
  c->node = node;
  return 0;
}

void gk_set_equation(gk_chromosome *c, char *equation) {
  c->node = convert_to_tree(equation, c->pool);
}

char *gk_to_string_full(gk_chromosome *c) {
  return convert_to_equation(c->node);
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
