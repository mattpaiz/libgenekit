#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "tree.h"
#include "simulation.h"

typedef struct {
  tree *node;
  function_pool *pool;
} chromosome;

chromosome *alloc_chromosome(gk_simulation *);
void gk_set_equation(chromosome *, char *);

int set_chromosome_node(chromosome *c, tree *node);
void free_chromosome(chromosome *c);

char *gk_to_string(chromosome *c);

#endif
