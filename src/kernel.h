#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "genekit.h"
#include "chromosome.h"
#include "simulation.h"

typedef struct {
  int (*init)(gk_simulation *);
  int (*populate)(gk_simulation *, gk_population *);
  gk_population *(*process)(gk_simulation *, gk_population *);
  int (*cleanup)(gk_simulation *, gk_population *);
  int (*terminate)(gk_population *, int); 
} gk_kernel;

int gk_run(gk_kernel *kernel, gk_simulation *sim);
gk_chromosome *gk_select(gk_population *population);

#endif
