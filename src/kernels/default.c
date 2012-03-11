#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "default.h"

int gk_default_populate(gk_simulation *sim, gk_population *population) {

 int i;

 for(i = 0; i < sim->population_size; i++) {
   population->individuals[i] = gk_alloc_chromosome(sim);
   gk_randomize_chromosome(population->individuals[i], sim->max_depth);
 }

 population->size = sim->population_size;

 return 0; 
}

int gk_default_terminate(gk_population *population, int generation) {
  return (generation >= 50000);
}

int gk_default_process(gk_simulation *sim, gk_population *population) {

 chromosome *male;
 chromosome *female;

 int i;

 chromosome **individuals = (chromosome **) malloc(sizeof(chromosome *) * population->size);

 for(i = 0; i < population->size / 4; i+=2) {
   male = gk_clone_chromosome(gk_select(population));
   female = gk_clone_chromosome(gk_select(population));

   crossover(&male->node, &female->node, sim->max_depth);
   individuals[i] = male;
   individuals[i + 1] = female;
 }

 for(i = population->size / 4; i < population->size; i++) {
   individuals[i] = gk_clone_chromosome(gk_select(population));
 }

 //Elitism?
 gk_free_chromosome(individuals[population->max_index]);
 individuals[population->max_index] = gk_clone_chromosome(population->individuals[population->max_index]);

 gk_clear_population(population);
 population->individuals = individuals;

 return 0; 
}

int gk_default_init(gk_simulation *sim) {
  srand(time(NULL));
  rand();

  return 0;
}

int gk_default_cleanup(gk_simulation *sim, gk_population *population) {
  return 0;
}


gk_kernel *gk_create_default_kernel() {

  gk_kernel *my_kernel = (gk_kernel *) malloc(sizeof(gk_kernel));
  my_kernel->init = &gk_default_init;
  my_kernel->populate = &gk_default_populate;
  my_kernel->process = &gk_default_process;
  my_kernel->terminate = &gk_default_terminate;
  my_kernel->cleanup = &gk_default_cleanup;

  return my_kernel;
}