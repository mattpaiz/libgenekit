#include <stdlib.h>

#include "tree.h"
#include "rand.h"
#include "mutate.h"

void crossover(tree **male, tree **female, int level) {

  int male_size = RAND(get_size(*male));  
  int female_size = RAND(get_size(*female));

  tree *m = get_node(*male, &male_size);
  tree *f = get_node(*female, &female_size);

  tree temp = *m;
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
