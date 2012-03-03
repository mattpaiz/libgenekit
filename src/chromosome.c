#include <stdlib.h>

#include "tree.h"
#include "chromosome.h"
#include "simulation.h"
#include "equation.h"

chromosome *alloc_chromosome(gk_simulation *simulation) { 

  chromosome *c = (chromosome *) malloc(sizeof(chromosome)); 
  c->pool = &simulation->pool;
  c->node = NULL;

  return c;
}

void free_chromosome(chromosome *c) {
  if(c->node) free_tree(c->node);
  free(c);
}

int set_chromosome_node(chromosome *c, tree *node) {
  c->node = node;
  return 0;
}

void gk_set_equation(chromosome *c, char *equation) {
  c->node = convert_to_tree(equation, c->pool);
}

char *gk_to_string(chromosome *c) {
  return convert_to_hr_equation(c->node); 
}
