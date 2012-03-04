#include <stdlib.h>

#include "tree.h"
#include "chromosome.h"
#include "equation.h"
#include "rand.h"

void gk_randomize_chromosome(chromosome *c, int depth) {
   if(c->node) free_tree(c->node);
   c->node = alloc_tree(get_branch_function(RAND(count_branch_functions(c->pool)), c->pool));
   append_random_node(c->node, c->pool, 0, depth);
}

chromosome *gk_clone_chromosome(chromosome *c) {
  chromosome *clone = (chromosome *) malloc(sizeof(chromosome));
  clone->score = c->score;
  clone->node = copy_tree(c->node);
  clone->pool = c->pool;

  return clone;
}

void gk_free_chromosome(chromosome *c) {
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
