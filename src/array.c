
#include "array.h"

////////////////////////
// Array definitions //
//////////////////////

typedef struct{
    double *data;
    size_t used;
    size_t cap;
} Array;

void array_init(Array *a, size_t size){

    double *ptr = malloc(size * sizeof(double));

    if (ptr == NULL){
        printf("Unable to allocate array.");
        free(ptr);
        exit(0);
    }
    else {
        a->data = ptr;
        a->used = 0;
        a->cap  = size;
    }
}

void array_add(Array *a, double element){
    if (a->used == a->cap) {
        if (a->cap == 0){
            a->cap = 1;
        }
        else {
            a->cap *= 2;
        }

        double *ptr = realloc(a->data, a->cap * sizeof(double));

        if (ptr == NULL){
            printf("Unable to add element to array.");
            free(ptr);
            exit(0);
        }
        else {
            a->data = ptr;
        }
    }
    a->data[a->used] = element;
    a->used++;
}

void array_free(Array *a){
    free(a->data);
    a->data = NULL;
    a->used = 0; 
    a->cap  = 0;
}

////////////////////////c/
// Matrix definitions //
///////////////////////

typedef struct{
    double *data;
    size_t nrows;
    size_t ncols;
    size_t used;
} Matrix;

void matrix_init(Matrix *m, size_t nrows, size_t ncols){

    double *ptr = malloc(nrows * ncols * sizeof(double));

    if (ptr == NULL){
        printf("Unable to allocate matrix.");
        free(ptr);
        exit(0);
    }
    else {
        m->data  = ptr;
        m->nrows = nrows;
        m->ncols = ncols;
        m->used  = 0;
    }
}

void matrix_add(Matrix *m, double element){
    int cap = m->ncols * m->nrows;
    if (m->used == cap) {
        if (cap == 0){
            m->ncols = 1;
            m->nrows = 1;
        }
        else {
            m->nrows = m->nrows + 1;
        }

        double *ptr = realloc(m->data, m->nrows * m->ncols * sizeof(double));

        if (ptr == NULL){
            printf("Unable to add element to Matrix.");
            free(ptr);
            exit(0);
        }
        else {
            m->data = ptr;
        }
    }
    m->data[m->used] = element;
    m->used++;
}

void matrix_free(Matrix *m){
    free(m->data);
    m->data  = NULL;
    m->nrows = 0; 
    m->ncols = 0;
    m->used  = 0;
}

////////////////////////
// Tests definitions //
//////////////////////

void test_array_init(){
    Array a;
    Array b;

    int N = 10;
    int M = 10;
     
    // Non zero size 
    array_init(&a, N);
    
    assert(a.data != NULL);
    assert(a.used == 0);
    assert(a.cap == N);

    array_free(&a);

    // Zero size
    array_init(&b, M);
    
    assert(b.data != NULL);
    assert(b.used == 0);
    assert(b.cap == M);

    array_free(&b);

}

void test_array_add(){
    Array a;
    
    int N = 2;

    double value1 = 112.0; 
    double value2 = 120.0; 
    double value3 = 120.0; 

    array_init(&a, N);

    array_add(&a, value1);
    assert(a.data[0] == value1);
    assert(a.used == 1);

    array_add(&a, value2);
    assert(a.data[1] == value2);
    assert(a.used == 2);

    // Add value and double cap
    array_add(&a, value3);
    assert(a.data[2] == value3);
    assert(a.used == 3);
    assert(a.cap == 4);

    array_free(&a);
    
}

void test_array_free(){
     Array a;
    
    int N = 3;

    double value1 = 112.0; 
    double value2 = 120.0; 
    double value3 = 120.0; 

    array_init(&a, N);

    array_add(&a, value1);
    array_add(&a, value2);
    array_add(&a, value3);
    
    array_free(&a);
    assert(a.data == NULL);
    assert(a.used == 0);
    assert(a.cap == 0);

}
