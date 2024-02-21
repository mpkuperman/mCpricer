
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
        a->cap *= 2;
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

/////////////////////////
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
    if (m->used == m->ncols * m->nrows) {
        m->nrows = m->nrows + 1;
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
