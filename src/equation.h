#ifndef __EQUATION_H__
#define __EQUATION_H__

#include "genekit.h"

gk_tree *gk_equation_convert(char *equation, gk_function_pool *pool);

char *gk_equation_alloc(gk_tree *);
char *gk_equation_alloc_hr(gk_tree *);

#endif
