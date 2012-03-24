/*
 * dna/vector.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../genekit.h"
#include "vector.h"

char *gk_vector_display_binary(CTYPE dna) {

  CTYPE chromosome = dna;

  char *buffer = (char *) malloc(sizeof(char) * (BITNUM + 1));

  int c;
  for(c = (BITNUM - 1); c >= 0; c--) {
    buffer[c] = (chromosome & 1) + '0';
    chromosome >>= 1;
  }
  buffer[BITNUM] = '\0';

  return buffer;
}

char *gk_vector_display(CTYPE dna) {

  char *buffer = (char *) malloc(sizeof(char) * 20);
  sprintf(buffer, "%f\n", gk_vector_evaluate(dna));

  return buffer;
}

void gk_vector_mutate(CTYPE *data) {
  int pos = RAND(BITNUM);
  *data ^= ((CTYPE) (1 << pos));
}

float gk_vector_evaluate(CTYPE dna) {

  double result = dna;

  result /= (((CTYPE) 1) << (BITNUM - 1));
  result /= 2.0;

  return (float) (GA_MIN + (result * (GA_MAX - GA_MIN)));
}

void gk_vector_crossover(CTYPE *data_a, CTYPE *data_b, int start, int end) {
  int index;
  CTYPE mask;
  for(index = start; index <= end; index++) {
    mask = (1 << index);
    if((*data_a & mask) != (*data_b & mask)) {
      *data_a ^= mask;
      *data_b ^= mask;
    }
  }
}
