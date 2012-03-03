#include <string.h>
#include <stdlib.h>
#include "function.h"

function *lookup_label(char *label, function_pool *pool) {

  int c;

  if(label[0] == '-' && (label[1] < 58 && label[1] > 47))
    return &pool->functions[2];

  if(label[0] < 58 && label[0] > 47) // If function is a primitive
    return &pool->functions[2];

  for(c = 0; c < pool->function_count; c++)
    if(!strcmp(label, pool->functions[c].label))
      return &pool->functions[c];

  return NULL;
}
