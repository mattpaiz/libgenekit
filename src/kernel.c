#include <stdlib.h>

#include "kernel.h"

int gk_run(gk_kernel *kernel, gk_simulation *sim) {

  int i, generation = 0;
  float fitness;

  gk_population *population;
  gk_chromosome *individual;
  population = gk_population_alloc(gk_simulation_get_population_size(sim));

  kernel->init(sim);
  kernel->populate(sim, population);

  while(!kernel->terminate(population, generation)) {

    gk_population_reset_max_values(population);

    for(i = 0; i < gk_population_get_size(population); i++) {
      individual = gk_population_get_individual(population, i);
      gk_chromosome_set_fitness(individual, fitness);
      gk_population_register_fitness(population, i);
    }

    gk_simulation_log(sim)(population, generation);

    population = kernel->process(sim, population);
    generation++;
  }

  kernel->cleanup(sim, population);
  gk_clear_population(population);

  return 0;
}

gk_chromosome *gk_select(gk_population *population) {

  float random = FRAND();
  float sum = 0;

  int c = 0;

  while((c < gk_population_get_size(population)) && (sum += (gk_chromosome_get_fitness(gk_population_get_individual(population, c++)) / gk_population_get_total_fitness(population))) < random);

  return gk_population_get_individual(population, c - 1);
}
