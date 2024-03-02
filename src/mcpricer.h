#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define S(i, j) S->data[j + i * S->ncols]

#include "array.c"
#include "random.c"
#include "gbm.c"
#include "payoff.c"