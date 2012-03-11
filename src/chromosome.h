#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "genekit.h"
#include "tree.h"
#include "function.h"

struct _gk_population {
  gk_chromosome **individuals;
  int size;
  float max_fitness;
  float total_fitness;
  int max_index;
};

struct _gk_chromosome {
  tree *node;
  gk_function_pool pool;
  float fitness;
};

void gk_set_equation(gk_chromosome *, char *);

int set_chromosome_node(gk_chromosome *c, tree *node);

char *gk_to_string(gk_chromosome *c);
gk_chromosome *gk_clone_chromosome(gk_chromosome *c);

void gk_free_chromosome(gk_chromosome *c);
void gk_free_population(gk_population *c);
void gk_clear_population(gk_population *c);

void gk_randomize_chromosome(gk_chromosome *c, int depth);

gk_chromosome *gk_alloc_chromosome(gk_simulation *);

#endif
