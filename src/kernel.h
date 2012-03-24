/*
 * kernel.h
 *
 * Copyright 2012 Matthew Paiz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "genekit.h"

struct _gk_kernel {
  int (*init)(gk_simulation *);
  int (*populate)(gk_kernel *, gk_simulation *, gk_population *);
  gk_population *(*process)(gk_simulation *, gk_population *);
  int (*cleanup)(gk_simulation *, gk_population *);
  int (*terminate)(gk_population *, int); 
  gk_function_pool *pool;
  void **bindings;
};

int gk_kernel_start(gk_kernel *kernel, gk_simulation *sim);
gk_function_pool *gk_kernel_get_function_pool(gk_kernel *kernel);
void gk_kernel_set_function_pool(gk_kernel *kernel, gk_function_pool *pool);

void *gk_kernel_get_binding(gk_kernel *, int);

#endif
