#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "genekit.h"
#include "tree.h"

struct _gk_population {
  gk_chromosome **individuals;
  int size;
  float max_fitness;
  float total_fitness;
  int max_index;
};

gk_population *gk_population_alloc(int);
void gk_set_equation(gk_chromosome *, char *);
gk_chromosome *gk_population_get_individual(gk_population *, int);
void gk_chromosome_set_fitness(gk_chromosome *c, float fitness);
float gk_chromosome_get_fitness(gk_chromosome *);
void gk_population_alloc_individual(gk_population *population, gk_simulation *simulation, int index);

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth);

int set_chromosome_node(gk_chromosome *c, gk_tree *node);

char *gk_to_string(gk_chromosome *c);
gk_chromosome *gk_clone_chromosome(gk_chromosome *c);

void gk_free_chromosome(gk_chromosome *c);
void gk_free_population(gk_population *c);
void gk_clear_population(gk_population *c);

void gk_randomize_chromosome(gk_chromosome *c, int depth);

gk_chromosome *gk_alloc_chromosome(gk_simulation *);

#endif
