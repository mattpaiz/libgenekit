#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "rand.h"
#include "chromosome.h"
#include "simulation.h"

typedef struct {
  int (*init)(gk_simulation *);
  int (*populate)(gk_simulation *, gk_population *);
  int (*process)(gk_simulation *, gk_population *);
  int (*cleanup)(gk_simulation *, gk_population *);
} gk_kernel;

int gk_run(gk_kernel *kernel, gk_simulation *sim);
chromosome *gk_select(gk_population *population);

#endif
