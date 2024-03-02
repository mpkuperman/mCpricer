
////////////////////////
// Array definitions //
//////////////////////

typedef struct{
    double *data;
    size_t used;
    size_t cap;
} Array;

void array_init(Array *a, size_t size);
void array_add(Array *a, double element);
void array_free(Array *a);

/////////////////////////
// Matrix definitions //
///////////////////////

typedef struct{
    double *data;
    size_t nrows;
    size_t ncols;
    size_t used;
} Matrix;

void matrix_init(Matrix *m, size_t nrows, size_t ncols);
void matrix_add(Matrix *m, double element);
void matrix_free(Matrix *m);

