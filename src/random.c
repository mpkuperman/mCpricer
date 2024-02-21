/* An implementation of the MT19937 Algorithm for the Mersenne Twister
 * by Evan Sultanik.  Based upon the pseudocode in: M. Matsumoto and
 * T. Nishimura, "Mersenne Twister: A 623-dimensionally
 * equidistributed uniform pseudorandom number generator," ACM
 * Transactions on Modeling and Computer Simulation Vol. 8, No. 1,
 * January pp.3-30 1998.
 *
 * http://www.sultanik.com/Mersenne_twister
 */

#define UPPER_MASK		0x80000000
#define LOWER_MASK		0x7fffffff
#define TEMPERING_MASK_B	0x9d2c5680
#define TEMPERING_MASK_C	0xefc60000

#include "random.h"

inline static void m_seedRand(MersenneTwister* rand, unsigned long seed) {
  /* set initial seeds to mt[STATE_VECTOR_LENGTH] using the generator
   * from Line 25 of Table 1 in: Donald Knuth, "The Art of Computer
   * Programming," Vol. 2 (2nd Ed.) pp.102.
   */
  rand->mt[0] = seed & 0xffffffff;
  for(rand->index=1; rand->index<STATE_VECTOR_LENGTH; rand->index++) {
    rand->mt[rand->index] = (6069 * rand->mt[rand->index-1]) & 0xffffffff;
  }
}


// Creates a new random number generator from a given seed.
MersenneTwister seedRand(unsigned long seed) {
  MersenneTwister rand;
  m_seedRand(&rand, seed);
  return rand;
}


// Generates a pseudo-randomly generated long.
unsigned long random_uniform_long(MersenneTwister* rand) {

  unsigned long y;
  static unsigned long mag[2] = {0x0, 0x9908b0df}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
  if(rand->index >= STATE_VECTOR_LENGTH || rand->index < 0) {
    /* generate STATE_VECTOR_LENGTH words at a time */
    int kk;
    if(rand->index >= STATE_VECTOR_LENGTH+1 || rand->index < 0) {
      m_seedRand(rand, 4357);
    }
    for(kk=0; kk<STATE_VECTOR_LENGTH-STATE_VECTOR_M; kk++) {
      y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
      rand->mt[kk] = rand->mt[kk+STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
    }
    for(; kk<STATE_VECTOR_LENGTH-1; kk++) {
      y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
      rand->mt[kk] = rand->mt[kk+(STATE_VECTOR_M-STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
    }
    y = (rand->mt[STATE_VECTOR_LENGTH-1] & UPPER_MASK) | (rand->mt[0] & LOWER_MASK);
    rand->mt[STATE_VECTOR_LENGTH-1] = rand->mt[STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
    rand->index = 0;
  }
  y = rand->mt[rand->index++];
  y ^= (y >> 11);
  y ^= (y << 7) & TEMPERING_MASK_B;
  y ^= (y << 15) & TEMPERING_MASK_C;
  y ^= (y >> 18);
  return y;
}


// Generates a pseudo-randomly generated double in the range [0..1]
inline double random_uniform(MersenneTwister* rand) {
  return((double)random_uniform_long(rand) / (unsigned long)0xffffffff);
}


double beasley_springer_moro(double u){
    double y;
    double r;
    double x;

    double a_0 = 2.50662823884;     double b_0 = -8.47351093090;
    double a_1 = -18.61500062529;   double b_1 = 23.08336743743;
    double a_2 = 41.39119773534;    double b_2 = -21.06224101826;
    double a_3 = -25.44106049637;   double b_3 = 3.13082909833;

    double c_0 = 0.3374754822726147; double c_5 = 0.0003951896511919;
    double c_1 = 0.9761690190917186; double c_6 = 0.0000321767881768;
    double c_2 = 0.1607979714918209; double c_7 = 0.0000002888167364;
    double c_3 = 0.0276438810333863; double c_8 = 0.0000003960315187;
    double c_4 = 0.0038405729373609;

    y = u - 0.5;

    if(fabs(y) < 0.42){
        r = y * y;
        x = y * (((a_3 * r + a_2) * r + a_1) * r + a_0) / ((((b_3 * r + b_2) * r + b_1) * r + b_0) * r + 1.0);
    } 
    else {
        r = u;
        if(y > 0){
            r = 1 - u;
        }
        r = log(-log(r));
        x = c_0 + r * (c_1 + r * (c_2 + r * (c_3 + r * (c_4 + r * (c_5 + r * (c_6 + r * (c_7 + r*c_8)))))));

        if(y < 0){
            x = -x;
        }
    }

    return x;
}

inline double random_normal(MersenneTwister* r){
  double x;
  double u;

  u = random_uniform(r);
  x = beasley_springer_moro(u);
  
  return x;
}