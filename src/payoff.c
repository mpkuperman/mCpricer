
#include "payoff.h"

double call(Matrix *S, double K){
    size_t N = S->nrows;
    size_t M = S->ncols;
    double pay = 0;

    double S_last;
    for (size_t i = 0; i < N; i++){
        S_last = S(i, M);
        if (S_last - K > 0){
            pay += S_last - K;
        }
    }
    return pay / N;
}

double put(Matrix *S, double K){
    size_t N = S->nrows;
    size_t M = S->ncols;
    double pay = 0;

    double S_last;
    for (size_t i = 0; i < N; i++){
        S_last = S(i, M);
        if (K - S_last > 0){
            pay += K - S_last;
        }
    }
    return pay / N;
}
