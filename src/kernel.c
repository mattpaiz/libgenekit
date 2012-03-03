#include <stdlib.h>
#include "kernel.h"

int gk_run(gk_kernel *kernel, gk_simulation *sim) {

  int i;

  gk_population population;
  population.individuals = (chromosome **) malloc(sizeof(chromosome *) * sim->population_size);
  population.size = 0;

  kernel->init(sim);
  kernel->populate(sim, &population);

  for(i = 0; i < 10; i++) {
    kernel->process(sim, &population);
    sim->log_generation(&population, i + 1);
  }

  kernel->cleanup(sim, &population);

  free(population.individuals);

  return 0;
}
