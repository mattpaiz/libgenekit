#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "genekit.h"

struct _gk_function {
  function_ptr ptr;
  int arg_count;
  char label[LABEL_LIMIT];
};

struct _gk_function_pool {
  gk_function *functions;
  int function_count;
};

gk_function *lookup_label(char * label, gk_function_pool pool);
gk_function *get_leaf_function(int index, gk_function_pool pool);
gk_function *get_branch_function(int index, gk_function_pool pool);

int count_leaf_functions(gk_function_pool pool);
int count_branch_functions(gk_function_pool pool);

#endif
