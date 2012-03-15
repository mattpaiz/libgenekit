/*
 * mutate.c
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

#include "tree.h"
#include "mutate.h"

void gk_mutate_crossover(gk_tree **male, gk_tree **female, int level) {

  int male_size = RAND(gk_tree_get_size(*male));  
  int female_size = RAND(gk_tree_get_size(*female));

  gk_tree *m = gk_tree_get_node(*male, &male_size);
  gk_tree *f = gk_tree_get_node(*female, &female_size);

  gk_tree *temp = gk_tree_alloc_empty();
  gk_tree_node_assign(temp, m);
  gk_tree_node_assign(m, f);

  if(gk_tree_get_max_level(*male) > level) {
    gk_tree_node_assign(m, temp);
    gk_tree_free(*male);
    *male = gk_tree_clone(f);
  } else {
    gk_tree_node_assign(f, temp);
    if(gk_tree_get_max_level(*female) > level) {
      gk_tree_free(*female);
      *female = gk_tree_clone(m);
    }
  }
}
