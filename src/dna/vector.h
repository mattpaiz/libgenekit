/*
 * dna/vector.h
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#define CTYPE unsigned int
#define BITNUM (sizeof(CTYPE) * 8)

#define GA_MAX 100 
#define GA_MIN 0

float gk_vector_evaluate(CTYPE dna);
char *gk_vector_display(CTYPE dna);
char *gk_vector_display_binary(CTYPE dna);
void gk_vector_crossover(CTYPE *data_a, CTYPE *data_b, int start, int end);
void gk_vector_mutate(CTYPE *data);

#endif
