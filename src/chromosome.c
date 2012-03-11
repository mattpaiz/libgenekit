#include <stdlib.h>

#include "tree.h"
#include "equation.h"
#include "simulation.h"
#include "function.h"
#include "chromosome.h"


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

int set_chromosome_node(gk_chromosome *c, tree *node) {
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
