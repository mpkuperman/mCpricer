#include "src/mcpricer.h"
#include <time.h>

int main(){

    // GBM  and Call option
    Matrix S;

    double M;
    double N;
    
    time_t start;
    time_t end;
    
    double S0 = 1.2;
    double mu = 1.0;
    double sg = 1.0;
    double T  = 1.0;

    int seed = 1234;
    
    M = 2;
    N = 100000;

    matrix_init(&S, N, M);

    start = clock();
    simulate(&S, S0, mu, sg, T, M, N, seed);
    
    double K = 0.9;
    double c;
    double p;

    c = call(&S, K);
    p = put(&S, K);

    end = clock();
    
    printf("Call price is: %f \n", c);
    printf("Put price is: %f \n", p);
    printf("Time taken: %f seconds", difftime(end, start) / CLOCKS_PER_SEC);
    
    matrix_free(&S);

    return 0;
}

