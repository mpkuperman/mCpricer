#include "src/mcpricer.h"

int main(){

#ifdef DEBUG

    test_array_add();
    test_array_init();
    test_array_free();
    test_array_insert();

    printf("All tests passed\n");

#endif

    return 0;

}

