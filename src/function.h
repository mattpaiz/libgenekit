#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#define DATATYPE float
#define LABEL_LIMIT 10

typedef DATATYPE(*function_ptr)(DATATYPE *); 

typedef struct {
  function_ptr ptr;
  int arg_count;
  char label[LABEL_LIMIT];
} function;

typedef struct {
  function *functions;
  int function_count;
} function_pool;

function *lookup_label(char * label, function_pool *pool);

#endif
