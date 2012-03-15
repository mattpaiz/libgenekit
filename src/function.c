/*
 * function.c
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

#include <string.h>
#include <stdlib.h>

#include "function.h"

struct _gk_function_pool {
  gk_function *functions;
  int function_count;
};

struct _gk_function {
  function_ptr ptr;
  int arg_count;
  char label[LABEL_LIMIT];
};

gk_function_pool *gk_function_pool_alloc() {
  gk_function_pool *pool = malloc(sizeof(gk_function_pool));
  pool->function_count = 0;
  return pool;
}

void gk_function_pool_add_function(gk_function_pool *pool, function_ptr ptr, int arg_count, char *label) {
  
  pool->functions = (pool->function_count) ? (gk_function *) realloc(pool->functions, sizeof(gk_function) * (pool->function_count + 1)) : 
    (gk_function *) malloc(sizeof(gk_function));
  pool->functions[pool->function_count].ptr = ptr;
  pool->functions[pool->function_count].arg_count = arg_count;
  strcpy(pool->functions[pool->function_count].label, label);
  pool->function_count++;
}

gk_function *gk_function_pool_get_random_function(gk_function_pool *pool) {
  return &pool->functions[RAND(pool->function_count)];
}

gk_function *gk_function_pool_get_function(gk_function_pool *pool, int index) {
  return &pool->functions[index];
}

function_ptr gk_function_invoke(gk_function *f) {
  return f->ptr;
}

int gk_function_get_arg_count(gk_function *f) {
  return f->arg_count;
}
char *gk_function_get_label(gk_function *f) {
  return f->label;
}

int gk_function_pool_count_leaves(gk_function_pool *pool) {
  int c, sum = 0;

  for(c = 0; c < pool->function_count; c++)
    if(pool->functions[c].arg_count == 0)
      sum++;

  return sum;
}

int gk_function_pool_count_branches(gk_function_pool *pool) {
  int c, sum = 0;

  for(c = 0; c < pool->function_count; c++)
    if(pool->functions[c].arg_count > 0)
      sum++;

  return sum;
}

gk_function *gk_function_pool_get_leaf(int index, gk_function_pool *pool) {

  int c;
  for(c = 0; c < pool->function_count; c++) {
    if(pool->functions[c].arg_count == 0) {
      if(index-- == 0)
        return &pool->functions[c];
    }
  }

  return NULL;
}

gk_function *gk_function_pool_get_branch(int index, gk_function_pool *pool) {

  int c;
  for(c = 0; c < pool->function_count; c++) {
    if(pool->functions[c].arg_count > 0) {
      if(index-- == 0)
        return &pool->functions[c];
    }
  }

  return NULL;
}

gk_function *gk_function_pool_lookup(char *label, gk_function_pool *pool) {

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
