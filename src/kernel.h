#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "simulation.h"
#include "chromosome.h"

typedef struct {
  int *(*init)(gk_simulation *);
  int (*create_population)(gk_simulation *, chromosome **);
  int (*cleanup)(gk_simulation *, chromosome **);
} gk_kernel;

int gk_run(gk_kernel *kernel, gk_simulation *sim);

#endif
