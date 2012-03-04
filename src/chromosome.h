#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "tree.h"

typedef struct {
  tree *node;
  function_pool *pool;
  float score;
} chromosome;

typedef struct gk_population {
  chromosome **individuals;
  int size;
  float max_fitness;
  float total_fitness;
  int max_index;
} gk_population;

void gk_set_equation(chromosome *, char *);

int set_chromosome_node(chromosome *c, tree *node);

char *gk_to_string(chromosome *c);
chromosome *gk_clone_chromosome(chromosome *c);

void gk_free_chromosome(chromosome *c);
void gk_free_population(gk_population *c);
void gk_clear_population(gk_population *c);

void gk_randomize_chromosome(chromosome *c, int depth);

#endif
