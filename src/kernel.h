#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "genekit.h"

typedef struct {
  int (*init)(gk_simulation *);
  int (*populate)(gk_simulation *, gk_population *);
  gk_population *(*process)(gk_simulation *, gk_population *);
  int (*cleanup)(gk_simulation *, gk_population *);
  int (*terminate)(gk_population *, int); 
} gk_kernel;

int gk_kernel_start(gk_kernel *kernel, gk_simulation *sim);

#endif
