#ifndef __MTWISTER_H
#define __MTWISTER_H

#define STATE_VECTOR_LENGTH 624
#define STATE_VECTOR_M      397 /* changes to STATE_VECTOR_LENGTH also require changes to this */

typedef struct tagMTRand {
  unsigned long mt[STATE_VECTOR_LENGTH];
  int index;
} MersenneTwister;

MersenneTwister seedRand(unsigned long seed);
unsigned long random_uniform_long(MersenneTwister* rand);
double random_uniform(MersenneTwister* rand);
double beasley_springer_moro(double u);
double random_normal(MersenneTwister *rand);

#endif /* #ifndef __MTWISTER_H */