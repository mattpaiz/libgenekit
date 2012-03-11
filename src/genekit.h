#ifndef __GENOME_H__
#define __GENOME_H__

#define DATATYPE float
#define LABEL_LIMIT 10
#define RAND(X) (rand() % X) 
#define FRAND() (((float) rand())/ ((float) RAND_MAX)) 

typedef DATATYPE(*function_ptr)(DATATYPE *); 

typedef struct _gk_chromosome gk_chromosome;
typedef struct _gk_population gk_population;
typedef struct _gk_simulation gk_simulation;
typedef struct _gk_function gk_function;
typedef struct _gk_function_pool gk_function_pool;

#endif
