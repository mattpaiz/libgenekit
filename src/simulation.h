#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "tree.h"
#include "function.h"
#include "chromosome.h"

typedef float(*fitness_ptr)(tree *); 

typedef struct {
  int population_size;
  int max_depth;
  function_pool pool;

  void(*log_generation)(gk_population *, int); 
  float(*fitness)(chromosome *); 
} gk_simulation;

void gk_set_population_size(gk_simulation *, int);
void gk_set_max_depth(gk_simulation *, int);
void gk_set_function_pool(gk_simulation *, function *, int);

chromosome *gk_alloc_chromosome(gk_simulation *);

gk_simulation *gk_create_simulation();

#endif
