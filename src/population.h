#ifndef __POPULATION_H__
#define __POPULATION_H__

#include "genekit.h"

gk_population *gk_population_alloc(int);
gk_chromosome *gk_population_get_individual(gk_population *, int);
gk_chromosome *gk_population_get_most_fit_individual(gk_population *population);
void gk_population_alloc_individual(gk_population *population, gk_simulation *simulation, int index);
void gk_population_reset_max_values(gk_population *);
int gk_population_get_size(gk_population *);
float gk_population_get_total_fitness(gk_population *);
int gk_population_get_max_index(gk_population *);
float gk_population_get_max_fitness(gk_population *);
void gk_population_set_individual(gk_population *population, int index, gk_chromosome *c);
void gk_population_register_fitness(gk_population *, int);
void gk_free_population(gk_population *c);
void gk_clear_population(gk_population *c);

#endif
