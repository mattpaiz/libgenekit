#include <string.h>
#include <stdlib.h>
#include "function.h"

int count_leaf_functions(function_pool pool) {
  int c, sum = 0;

  for(c = 0; c < pool.function_count; c++)
    if(pool.functions[c].arg_count == 0)
      sum++;

  return sum;
}

int count_branch_functions(function_pool pool) {
  int c, sum = 0;

  for(c = 0; c < pool.function_count; c++)
    if(pool.functions[c].arg_count > 0)
      sum++;

  return sum;
}

gk_function *get_leaf_function(int index, function_pool pool) {

  int c;
  for(c = 0; c < pool.function_count; c++) {
    if(pool.functions[c].arg_count == 0) {
      if(index-- == 0)
        return &pool.functions[c];
    }
  }

  return NULL;
}

gk_function *get_branch_function(int index, function_pool pool) {

  int c;
  for(c = 0; c < pool.function_count; c++) {
    if(pool.functions[c].arg_count > 0) {
      if(index-- == 0)
        return &pool.functions[c];
    }
  }

  return NULL;
}

gk_function *lookup_label(char *label, function_pool pool) {

  int c;

  if(label[0] == '-' && (label[1] < 58 && label[1] > 47))
    return &pool.functions[2];

  if(label[0] < 58 && label[0] > 47) // If function is a primitive
    return &pool.functions[2];

  for(c = 0; c < pool.function_count; c++)
    if(!strcmp(label, pool.functions[c].label))
      return &pool.functions[c];

  return NULL;
}
