#include "src/mcpricer.h"
#include <time.h>

int main(){

#ifdef DEBUG

    test_array_init();
    test_array_add();
    test_array_free();

    printf("All tests passed\n");

    return 0;

#endif

}

