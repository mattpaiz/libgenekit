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

    population->max_index = 0;
    population->total_fitness = 0;

    for(i = 0; i < population->size; i++) {
      individual = gk_population_get_individual(population, i);
      population->total_fitness += (fitness = gk_simulation_fitness(sim)(individual));
      gk_chromosome_set_fitness(individual, fitness);

      if(fitness > population->max_fitness) {
        population->max_index = i;
        population->max_fitness = fitness;
      }
    }
    population->max_fitness = gk_chromosome_get_fitness(gk_population_get_individual(population, population->max_index));
    gk_simulation_log(sim)(population, generation);

    kernel->process(sim, population);
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

  while((c < population->size) && (sum += (gk_chromosome_get_fitness(gk_population_get_individual(population, c++)) / population->total_fitness)) < random);

  return population->individuals[c - 1];
}
