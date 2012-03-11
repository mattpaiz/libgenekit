#ifndef __EQUATION_H__
#define __EQUATION_H__

#include <string.h>

#include "function.h"
#include "tree.h"

int first_arg_length(char *left);
tree *convert_to_tree(char *equation, function_pool pool);

char *convert_to_equation(tree *);
char *convert_to_hr_equation(tree *);

#endif
