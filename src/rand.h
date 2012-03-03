#ifndef __RAND_H__
#define __RAND_H__

#define RAND(X) (rand() % X) 
#define FRAND() (((float) rand())/ ((float) RAND_MAX)) 

#endif
