#include <genekit/simulation.h>
#include <genekit/chromosome.h>
#include <genekit/tree.h>
#include <genekit/mutate.h>
#include <genekit/kernel.h>
#include <genekit/kernels/default.h>

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define POPULATION_SIZE 100
#define MAX_DEPTH 10

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
  return (data[1] != 0) ? data[0] / data[1] : 100000;
}

float primitive(float *data) {
  return data[0];
}

float fitness(chromosome *c) {
  return 0;
}

function all_functions[] = {
  {&addition, 2, "+"},
  {&subtraction, 2, "-"},
  {&primitive, 0, "#"},
  {&division, 2, "/"},
  {&multiplication, 2, "*"},
};

int main(void) {

  gk_simulation *simulation = gk_simulation_alloc();

  gk_simulation_set_population_size(simulation, 100);
  gk_simulation_set_max_depth(simulation, 5);
  gk_simulation_set_function_pool(simulation, all_functions, 5);
  gk_simulation_set_fitness(simulation, &fitness);

  gk_kernel *my_kernel = gk_create_default_kernel();
  gk_run(my_kernel, simulation);

  gk_simulation_free(simulation);

  return 0;
}


