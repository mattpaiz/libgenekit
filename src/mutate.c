#include <stdlib.h>

#include "tree.h"
#include "mutate.h"

void crossover(gk_tree **male, gk_tree **female, int level) {

  int male_size = RAND(get_size(*male));  
  int female_size = RAND(get_size(*female));

  gk_tree *m = get_node(*male, &male_size);
  gk_tree *f = get_node(*female, &female_size);

  gk_tree temp = *m;
  *m = *f;

  if(get_max_level(*male) > level) {
    *m = temp;
    free_tree(*male);
    *male = copy_tree(f);
  } else {
    *f = temp;
    if(get_max_level(*female) > level) {
      free_tree(*female);
      *female = copy_tree(m);
    }
  }
}
