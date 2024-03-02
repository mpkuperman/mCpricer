
#include "gbm.h"

void simulate(Matrix *S, double S0, double mu, double sg, double T, int M, int N, int seed){
    
    double dt = T / M;

    double mu_term = (mu - sg * sg / 2.0) * dt;
    double sg_term = sg * sqrt(dt);

    double Z;
    MersenneTwister r = seedRand(seed);

    for (size_t i = 0; i < N; i++){
        S(i, 0) = S0;
        for(size_t j = 1; j < M; j++){
            Z = random_normal(&r);
            S(i, j) = S(i, j - 1) * exp(mu_term + sg_term * Z);
        }    
    }
}

