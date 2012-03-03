#include <stdlib.h>
#include "kernel.h"

int gk_run(gk_kernel *kernel, gk_simulation *sim) {

  chromosome **population = (chromosome **) malloc(sizeof(chromosome *) * sim->population_size);

  kernel->init(sim);
  kernel->create_population(sim, population);
  kernel->cleanup(sim, population);

  return 0;
}
