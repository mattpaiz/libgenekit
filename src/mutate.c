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
