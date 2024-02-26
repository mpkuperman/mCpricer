
#include "gbm.h"

void simulate(Matrix *S, double S0, double mu, double sg, double T, int M, int N, int seed){
    
    double dt = T / M;

    double mu_term = (mu - sg * sg / 2.0) * dt;
    double sg_term = sg * sqrt(dt);

    double Z;
    MersenneTwister r = seedRand(seed);

    for (size_t i = 0; i < N; i++){
        S->data[i * S->ncols] = S0;
        for(size_t j = 1; j < M; j++){
            Z = random_normal(&r);
            S->data[j + i * S->ncols] = S->data[j - 1 + i * S->ncols] * exp(mu_term + sg_term * Z);
        }    
    }
}

