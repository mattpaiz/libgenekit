/*
 * symreg.c
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
#include <genekit/function.h>
#include <genekit/kernel.h>
#include <genekit/kernels/sr.h>

#include <stdlib.h>
#include <math.h>

#define POPULATION_SIZE 100
#define MAX_DEPTH 4 

float addition(float *data) {
  return data[0] + data[1];
}

float multiplication(float *data) {
  return data[0] * data[1];
}

float subtraction(float *data) {
  return data[0] - data[1];
}

float division(float *data) {
  return (data[1] != 0) ? data[0] / data[1] : 0;
}

float primitive(float *data) {
  return data[0];
}

float fitness(gk_chromosome *c) {
  return 1.0 / fabs(3.1415927 - gk_chromosome_evaluate(c));
}

int main(void) {

  gk_simulation *simulation = gk_simulation_alloc();

  gk_simulation_set_population_size(simulation, POPULATION_SIZE);
  gk_simulation_set_max_depth(simulation, MAX_DEPTH);
  gk_simulation_set_fitness(simulation, &fitness);

  gk_function_pool *pool = gk_function_pool_alloc();
  gk_function_pool_add_function(pool, &addition, 2, "+");
  gk_function_pool_add_function(pool, &subtraction, 2, "-");
  gk_function_pool_add_function(pool, &primitive, 0, "#");
  gk_function_pool_add_function(pool, &division, 2, "/");
  gk_function_pool_add_function(pool, &multiplication, 2, "*");

  gk_kernel *my_kernel = gk_create_sr_kernel();
  gk_kernel_set_function_pool(my_kernel, pool);
  gk_kernel_start(my_kernel, simulation);

  gk_function_pool_free(pool);
  gk_simulation_free(simulation);

  return 0;
}


