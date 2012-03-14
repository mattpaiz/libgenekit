#include <stdlib.h>

#include "tree.h"
#include "mutate.h"

void gk_mutate_crossover(gk_tree **male, gk_tree **female, int level) {

  int male_size = RAND(get_size(*male));  
  int female_size = RAND(get_size(*female));

  gk_tree *m = get_node(*male, &male_size);
  gk_tree *f = get_node(*female, &female_size);

  gk_tree *temp = gk_tree_alloc_empty();
  gk_tree_node_assign(temp, m);
  gk_tree_node_assign(m, f);

  if(get_max_level(*male) > level) {
    gk_tree_node_assign(m, temp);
    free_tree(*male);
    *male = copy_tree(f);
  } else {
    gk_tree_node_assign(f, temp);
    if(get_max_level(*female) > level) {
      free_tree(*female);
      *female = copy_tree(m);
    }
  }
}
