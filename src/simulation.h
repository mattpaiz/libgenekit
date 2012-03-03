#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "tree.h"
//#include "settings.h"
#include "function.h"
//#include "record.h"

#if HUMAN_READABLE 
#define DISPLAY_EQUATION convert_to_hr_equation
#else
#define DISPLAY_EQUATION convert_to_equation
#endif

typedef float(*fitness_ptr)(tree *); 

typedef struct {
  float *data;
  int size;
} dataset;

typedef struct {
  int erpa_level;
  function_pool default_pool;
  function *all_functions;
  function_pool terminal_pool;
  fitness_ptr fitness_function;
  char directory[100];
  dataset input_data;
} simulation;

typedef struct {
  int population_size;
  int max_depth;
  function_pool pool;
} gk_simulation;

void gk_set_population_size(gk_simulation *, int);
void gk_set_max_depth(gk_simulation *, int);
void gk_set_function_pool(gk_simulation *, function *, int);

gk_simulation *gk_create_simulation();

#endif
