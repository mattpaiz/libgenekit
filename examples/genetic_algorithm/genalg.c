/*
 * genalg.c
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

#include <genekit/simulation.h>
#include <genekit/chromosome.h>
#include <genekit/kernel.h>
#include <genekit/kernels/ga.h>

#include <math.h>

#define POPULATION_SIZE 1000

float fitness(gk_chromosome *c) {
  float x = gk_chromosome_evaluate(c);
  return 1.0 / fabs(x*x - 3.1415927);
}

int main(void) {

  gk_simulation *simulation = gk_simulation_alloc();

  gk_simulation_set_population_size(simulation, POPULATION_SIZE);
  gk_simulation_set_fitness(simulation, &fitness);

  gk_kernel *my_kernel = gk_create_ga_kernel();
  gk_kernel_start(my_kernel, simulation);

  gk_simulation_free(simulation);

  return 0;
}


