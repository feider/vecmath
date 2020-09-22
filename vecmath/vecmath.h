
#include <stddef.h>

typedef struct {
    size_t size;
    double * values;

} Vector;

Vector * vecm_vector_create(size_t length);

void vecm_vector_init(Vector * vector, size_t size, double values);

void vecm_vector_destroy(Vector * vec);

void vecm_vector_set(Vector * vec, const double * values);

void vecm_vector_add(Vector * vec1, Vector * vec2, Vector * result);

double vecm_vector_dprod(Vector * vec1, Vector * vec2);

void vecm_vector_cprod(Vector * vec1, Vector * vec2, Vector * result);

double vecm_vector_length();

void vecm_vector_smult(Vector * vec, double scalar, Vector * result);

void vecm_vector_sdiv(Vector * vec, double scalar, Vector * result);

double vecm_vector_len(Vector * vec);

void vecm_vector_from_deg(Vector * vec, double angle, double length);

void print_vector(Vector * vec);

typedef struct {
    size_t columns;
    size_t rows;
    size_t size;
    double * values;
} Matrix;

Matrix * vecm_mat_create(size_t rows, size_t columns);

void vecm_mat_destroy(Matrix * mat);

void vecm_mat_add(Matrix * mat1, Matrix * mat2, Matrix * result);

void vecm_mat_fill(Matrix * mat, double value);

void vecm_mat_setat(Matrix * mat, size_t row, size_t column, double value);

void print_matrix(Matrix * mat);
