#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "genekit.h"

struct _gk_function_pool {
  gk_function *functions;
  int function_count;
};

gk_function *lookup_label(char * label, gk_function_pool pool);
gk_function *get_leaf_function(int index, gk_function_pool pool);
gk_function *get_branch_function(int index, gk_function_pool pool);
gk_function *gk_function_pool_get_function(gk_function_pool pool, int index);
gk_function_pool *gk_function_pool_alloc();

void gk_function_pool_add_function(gk_function_pool *pool, function_ptr ptr, int arg_count, char *label);

char *gk_function_get_label(gk_function *f);
int gk_function_get_arg_count(gk_function *f);
function_ptr gk_function_invoke(gk_function *f);

int count_leaf_functions(gk_function_pool pool);
int count_branch_functions(gk_function_pool pool);

#endif
