#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "genekit.h"

gk_function_pool *gk_function_pool_alloc();

gk_function *gk_function_pool_lookup(char * label, gk_function_pool *pool);
void gk_function_pool_add_function(gk_function_pool *pool, function_ptr ptr, int arg_count, char *label);

gk_function *gk_function_pool_get_leaf(int index, gk_function_pool *pool);
gk_function *gk_function_pool_get_branch(int index, gk_function_pool *pool);
gk_function *gk_function_pool_get_function(gk_function_pool *pool, int index);
gk_function *gk_function_pool_get_random_function(gk_function_pool *pool);
int gk_function_get_arg_count(gk_function *f);
int gk_function_pool_count_leaves(gk_function_pool *pool);
int gk_function_pool_count_branches(gk_function_pool *pool);

char *gk_function_get_label(gk_function *f);
function_ptr gk_function_invoke(gk_function *f);

#endif
