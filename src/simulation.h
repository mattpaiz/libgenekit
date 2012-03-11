#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "tree.h"
#include "function.h"
#include "chromosome.h"

typedef float(*gk_fitness_function)(chromosome *);
typedef void(*gk_log_function)(gk_population *, int);

typedef struct _gk_simulation gk_simulation;

gk_fitness_function gk_simulation_fitness(gk_simulation *);
gk_log_function gk_simulation_log(gk_simulation *);

void gk_simulation_set_population_size(gk_simulation *, int);
void gk_simulation_set_max_depth(gk_simulation *, int);
void gk_simulation_set_function_pool(gk_simulation *, function *, int);
void gk_simulation_set_fitness(gk_simulation *, gk_fitness_function);

int gk_simulation_get_population_size(gk_simulation *);
int gk_simulation_get_max_depth(gk_simulation *);

gk_simulation *gk_simulation_alloc();
void gk_simulation_free(gk_simulation *);

chromosome *gk_alloc_chromosome(gk_simulation *);

#endif
