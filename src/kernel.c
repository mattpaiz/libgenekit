#include <stdlib.h>

#include "kernel.h"

int gk_run(gk_kernel *kernel, gk_simulation *sim) {

  int i, generation = 0;

  gk_population population;
  population.individuals = (chromosome **) malloc(sizeof(chromosome *) * gk_simulation_get_population_size(sim));

  kernel->init(sim);
  kernel->populate(sim, &population);

  while(!kernel->terminate(&population, generation)) {

    population.max_index = 0;
    population.total_fitness = 0;
    for(i = 0; i < population.size; i++) {
      population.total_fitness += (population.individuals[i]->score = gk_simulation_fitness(sim)(population.individuals[i]));
      if(population.individuals[i]->score > population.individuals[population.max_index]->score)
        population.max_index = i;
    }
    population.max_fitness = population.individuals[population.max_index]->score;
    gk_simulation_log(sim)(&population, generation);

    kernel->process(sim, &population);
    generation++;
  }

  kernel->cleanup(sim, &population);
  gk_clear_population(&population);

  return 0;
}

chromosome *gk_select(gk_population *population) {

  float random = FRAND();
  float sum = 0;

  int c = 0;

  while((c < population->size) && (sum += (population->individuals[c++]->score / population->total_fitness)) < random);

  return population->individuals[c - 1];
}
