#ifndef __EQUATION_H__
#define __EQUATION_H__

#include "genekit.h"

int first_arg_length(char *left);
gk_tree *convert_to_tree(char *equation, gk_function_pool *pool);

char *convert_to_equation(gk_tree *);
char *convert_to_hr_equation(gk_tree *);

#endif
