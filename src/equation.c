#include <stdlib.h>
#include <stdio.h>

#include "equation.h"

int first_arg_length(char *left) {
  int c = 0, depth = 0;

  while(*(left + c)) {
    if(*(left + c) == ',' && !depth)
      return c;
    else if(*(left + c) == '(') 
      depth++;
    else if(*(left + c) == ')')
      depth--;
    c++;
  }

  return (c - 1);
}

char *convert_to_hr_equation(tree *node) {

  int c, label_length; 
  char *buffer, *out;

  int hr = 0;

  if(node->f->label[0] == '#') {
    char thebuffer[20];

    if(node->primitive > ((int)node->primitive))
      label_length = sprintf(thebuffer, "%f", node->primitive);
    else
      label_length = sprintf(thebuffer, "%d", ((int)node->primitive));

    buffer = (char *) malloc(sizeof(char) * (label_length + 1)); //TODO: Look into reducing size
    strcpy(buffer,thebuffer);
  } else if(node->f->label[0] == '+' || node->f->label[0] == '-' || node->f->label[0] == '*' || node->f->label[0] == '/' || node->f->label[0] == '^') {
    hr = 1;
    label_length = strlen(node->f->label);
    buffer = (char *) malloc(sizeof(char) * 2);
    strcpy(buffer,"\0");
  } else {
    if(node->f->label[0] != '_') {
      label_length = strlen(node->f->label);
      buffer = (char *) malloc(sizeof(char) * (label_length + 3));
      strcpy(buffer,node->f->label);
    } else {
      buffer = (char *) malloc(sizeof(char) * 1);
      strcpy(buffer,"\0");
    }
  }

  if(node->f->label[0] != '#' && node->f->label[0] != 'x' && node->f->label[0] != '_' && node->f->arg_count > 0)
    strcat(buffer, "(");

  char *tmp;

  for(c = 0; c < node->f->arg_count; c++) {
    out = convert_to_hr_equation(node->args[c]);

    if(node->args[c]->f == node->f && hr) {
      tmp = malloc(sizeof(char) * strlen(out)); //TODO: Size check
      tmp = strcpy(tmp, out + 1);
      tmp[strlen(tmp) - 1] = '\0';
      free(out);
      out = tmp;
    }

    buffer = (char *) realloc(buffer, sizeof(char) * (strlen(buffer) + strlen(out) + 3));

    strcat(buffer, out);

    if(!hr) {
      //If comma isn't appended, allocated memory is not wasted since it will be used for the 
      //last paranthesis
      if(c < (node->f->arg_count - 1)) strcat(buffer, ",");
    } else {
      if(c < (node->f->arg_count - 1)) strcat(buffer, node->f->label);
    }

    free(out);
  }

  if(node->f->label[0] != '#' && node->f->label[0] != 'x' && node->f->label[0] != '_' && node->f->arg_count > 0)
    strcat(buffer, ")");

  return buffer;

}

char *convert_to_equation(tree *node) {

  int c, label_length; 
  char *buffer, *out;

  if(node->f->label[0] == '#') {
    char thebuffer[20];

    if(node->primitive > ((int)node->primitive))
      label_length = sprintf(thebuffer, "%f", node->primitive);
    else
      label_length = sprintf(thebuffer, "%d", ((int)node->primitive));

    buffer = (char *) malloc(sizeof(char) * (label_length + 3));
    strcpy(buffer,thebuffer);
  } else {
    label_length = strlen(node->f->label);
    buffer = (char *) malloc(sizeof(char) * (label_length + 3));
    strcpy(buffer,node->f->label);
  }

  strcat(buffer, "(");

  for(c = 0; c < node->f->arg_count; c++) {
    out = convert_to_equation(node->args[c]);

    buffer = (char *) realloc(buffer, sizeof(char) * (strlen(buffer) + strlen(out) + 3));
    strcat(buffer, out);

    //If comma isn't appended, allocated memory is not wasted since it will be used for the 
    //last paranthesis
    if(c < (node->f->arg_count - 1)) strcat(buffer, ",");

    free(out);
  }

  strcat(buffer, ")");
  return buffer;
}

tree *convert_to_tree(char *equation, function_pool *pool) {

  function *function; 
  tree *output;

  int arg_length, c;

  char *buffer = (char *) malloc(sizeof(char) * (strlen(equation) + 1));

  char *left = equation;
  char *right = equation + strlen(equation) - 1;

  if(!strstr(equation, "(") &&  !strstr(equation, ")"))
    return NULL;

  while(*(left++) != '(');
  while(*(right--) != ')');

  strcpy(buffer, equation);
  buffer[left - equation - 1] = '\0';

  function = lookup_label(buffer, pool);

  output = alloc_tree(function);

  if(function->label[0] == '#')
    output->primitive = atof(buffer);

  for(c = 0; c < function->arg_count; c++) {
    arg_length = first_arg_length(left);
    strncpy(buffer, left, arg_length); 
    buffer[arg_length] = '\0';

    left += arg_length + 1;
    output->args[c] = convert_to_tree(buffer, pool);
  }

  free(buffer);
    
  return output;
}
