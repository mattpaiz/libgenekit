#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "tree.h"

typedef struct {
  tree *node;
  function_pool *pool;
} chromosome;

typedef struct gk_population {
  chromosome **individuals;
  int size;
  float max_fitness;
} gk_population;

void gk_set_equation(chromosome *, char *);

int set_chromosome_node(chromosome *c, tree *node);
void free_chromosome(chromosome *c);

char *gk_to_string(chromosome *c);

#endif
