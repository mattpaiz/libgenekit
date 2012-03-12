#include <genekit/simulation.h>
#include <genekit/chromosome.h>
#include <genekit/function.h>
#include <genekit/mutate.h>
#include <genekit/kernel.h>
#include <genekit/kernels/default.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define POPULATION_SIZE 100
#define MAX_DEPTH 10

float addition(float *data) {
  return data[0] + data[1];
}

float myfabs(float i) {
  return (i < 0) ? -i : i;
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
  return 1.0 / myfabs(3.1415927 - gk_chromosome_evaluate(c));
}

int main(void) {

  gk_simulation *simulation = gk_simulation_alloc();

  gk_simulation_set_population_size(simulation, 1000);
  gk_simulation_set_max_depth(simulation, 10);
  gk_simulation_set_fitness(simulation, &fitness);

  gk_function_pool *pool = gk_function_pool_alloc();

  gk_function_pool_add_function(pool, &addition, 2, "+");
  gk_function_pool_add_function(pool, &subtraction, 2, "-");
  gk_function_pool_add_function(pool, &primitive, 0, "#");
  gk_function_pool_add_function(pool, &division, 2, "/");
  gk_function_pool_add_function(pool, &multiplication, 2, "*");

  gk_simulation_set_function_pool(simulation, pool);

  gk_kernel *my_kernel = gk_create_default_kernel();
  gk_run(my_kernel, simulation);

  gk_simulation_free(simulation);

  return 0;
}


