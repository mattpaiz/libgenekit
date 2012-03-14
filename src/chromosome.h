#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "genekit.h"

gk_chromosome *gk_chromosome_alloc(gk_simulation *);
gk_chromosome *gk_chromosome_clone(gk_chromosome *c);
void gk_chromosome_free(gk_chromosome *c);

void gk_chromosome_crossover(gk_chromosome *a, gk_chromosome *b, int max_depth);
void gk_chromosome_randomize(gk_chromosome *c, int depth);
char *gk_chromosome_to_string(gk_chromosome *c);
char *gk_chromosome_to_string_full(gk_chromosome *c);
float gk_chromosome_evaluate(gk_chromosome *c);

float gk_chromosome_get_fitness(gk_chromosome *);

void gk_chromosome_set_equation(gk_chromosome *, char *);
void gk_chromosome_set_fitness(gk_chromosome *c, float fitness);
int gk_chromosome_set_node(gk_chromosome *c, gk_tree *node);


#endif
