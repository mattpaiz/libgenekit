#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "genekit.h"
#include "tree.h"

char *gk_to_string(gk_chromosome *c);
gk_chromosome *gk_clone_chromosome(gk_chromosome *c);
void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth);
int set_chromosome_node(gk_chromosome *c, gk_tree *node);
void gk_set_equation(gk_chromosome *, char *);
void gk_chromosome_set_fitness(gk_chromosome *c, float fitness);
float gk_chromosome_get_fitness(gk_chromosome *);
float gk_chromosome_evaluate(gk_chromosome *c);
char *gk_to_string_full(gk_chromosome *c);
void gk_free_chromosome(gk_chromosome *c);
void gk_randomize_chromosome(gk_chromosome *c, int depth);
gk_chromosome *gk_alloc_chromosome(gk_simulation *);


#endif
