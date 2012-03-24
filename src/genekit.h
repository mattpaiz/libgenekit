/*
 * genekit.h
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

#ifndef __GENEKIT_H__
#define __GENEKIT_H__

#define DATATYPE float
#define LABEL_LIMIT 10
#define RAND(X) (rand() % X) 
#define FRAND() (((float) rand())/ ((float) RAND_MAX)) 

#define GK_BINDING_COUNT 4

#define GK_KERNEL_BINDING_CROSSOVER  0
#define GK_KERNEL_BINDING_DISPLAY    1
#define GK_KERNEL_BINDING_RANDOMIZE  2
#define GK_KERNEL_BINDING_MUTATE     3

typedef DATATYPE(*function_ptr)(DATATYPE *); 

typedef struct _gk_chromosome gk_chromosome;
typedef struct _gk_population gk_population;
typedef struct _gk_simulation gk_simulation;
typedef struct _gk_function gk_function;
typedef struct _gk_function_pool gk_function_pool;
typedef struct _gk_tree gk_tree;
typedef struct _gk_kernel gk_kernel;

#endif
