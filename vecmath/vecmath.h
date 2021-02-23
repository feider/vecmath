#ifndef VECMATH_H 
#define VECMATH_H

#include <stddef.h>

typedef struct {
    size_t size;
    double * values;

} Vector;

/*
Vector * vecm_vector_create(size_t length);

void vecm_vector_init(Vector * vector, size_t size, double values);

void vecm_vector_destroy(Vector * vec);

void vecm_vector_set(Vector * vec, const double * values);

void vecm_vector_add(Vector * vec1, Vector * vec2, Vector * result);
void vecm_vec_add(double * vec1, double * vec2, double * result, size_t size);
void vecm_vec_sub(double * vec1, double * vec2, double * result, size_t size);

void vecm_vec2d_hom_from_points(double * p1, double * p2, double * homogenous);
void vecm_vec2d_normal(double * p1, double * p2, double * normal);

double vecm_vector_dprod(Vector * vec1, Vector * vec2);
double vecm_vec_dprod(double * vec1, double * vec2, size_t size);


void vecm_vec_cprod(double * vec1, double * vec2, double * result);

void vecm_vector_smult(Vector * vec, double scalar, Vector * result);
void vecm_vec_smult(double * vec, double scalar, double * result, size_t size);

void vecm_vec_sdiv(double * vec, double scalar, double * result, size_t size);

double vecm_vector_len(Vector * vec);
double vecm_vec_len(double * vec, size_t size);

void vecm_vector_from_deg(Vector * vec, double angle, double length);

void vecm_vec2d_from_deg(double * vec, double angle, double length);
double vecm_vec2d_vec_to_deg(double * vec);

void print_vector(Vector * vec);
void print_vec(double * vec, size_t size); */

typedef struct {
    size_t columns;
    size_t rows;
    size_t size;
    double * values;
} Matrix;
/*

Matrix * vecm_mat_create(size_t rows, size_t columns);

void vecm_mat_destroy(Matrix * mat);

void vecm_mat_add(Matrix * mat1, Matrix * mat2, Matrix * result);

void vecm_mat_fill(Matrix * mat, double value);

void vecm_mat_setat(Matrix * mat, size_t row, size_t column, double value);

void print_matrix(Matrix * mat);
*/

// implementation 
//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// helper code

static inline double vecm_to_rad(double deg)
{
    return deg * 3.14159 / 180.0;
}
static inline double vecm_to_deg(double rad)
{
    return 180 * rad / 3.14159;
}

/* Vector code */

static inline Vector * vecm_vector_create(size_t size)
{
    Vector * vec = (Vector *) malloc(sizeof(Vector));
    vec->size = size;
    vec->values = (double*) malloc(size * sizeof(double));
    return vec;
}

static inline void vecm_vector_init(Vector * vec, size_t size, double values)
{
    vec->size = size;
    vec->values = (double*) malloc(size * sizeof(double));
    memset(vec->values, values, vec->size);
}

static inline void vecm_vector_destroy(Vector * vec)
{
    free(vec->values);
    free(vec);
}

static inline void vecm_vector_set(Vector * vec, const double * values)
{
    memcpy((void*) vec->values, (void*) values, vec->size*sizeof(double));
}

static inline void vecm_vector_add(Vector * vec1, Vector * vec2, Vector * result)
{
    if ((vec1->size != vec2->size) ||
            (vec2->size != result->size))
    {
        exit(1);// error, vectors don't have the same size!
    }

    for(size_t l = 0; l<vec1->size; l++)
    {
        result->values[l] = vec1->values[l] + vec2->values[l];
    }
}

static inline void vecm_vec_add(double * vec1, double * vec2, double * result, size_t size)
{
    for(size_t l = 0; l<size; l++)
    {
        result[l] = vec1[l] + vec2[l];
    }
}
static inline void vecm_vec_sub(double * vec1, double * vec2, double * result, size_t size)
{
    for(size_t l = 0; l<size; l++)
    {
        result[l] = vec1[l] - vec2[l];
    }
}

static inline void vecm_vec2d_hom_from_points(double * p1, double * p2, double * homogenous)
{
    homogenous[0] = p1[1]-p2[1];
    homogenous[1] = p2[0]-p1[0];
    homogenous[2] = -( (p2[0]*p1[1]) - (p1[0]*p2[1]) );
}

static inline double vecm_vec_len(double * vec, size_t size)
{
    double retval = 0;
    for (size_t i = 0; i < size; i++)
        retval += (vec[i] * vec[i]);
    return sqrt(retval);
}

static inline void vecm_vec_sdiv(double * vec, double scalar, double * result, size_t size)
{
    for (size_t i = 0; i < size; i++)
        result[i] = vec[i]/scalar;
}

static inline void vecm_vec2d_normal(double * p1, double * p2, double * normal)
{
    double dx = p2[0] - p1[0];
    double dy = p2[1] - p1[1];
    normal[0] = -dy;
    normal[1] = dx;
    double len = vecm_vec_len(normal, 2);
    vecm_vec_sdiv(normal, len, normal, 2);
}

static inline double vecm_vector_dprod(Vector * vec1, Vector * vec2)
{
    if (vec1->size != vec2->size)
    {
        exit(1); // error, vectors don't have the same size!
    }

    double result = 0;
    for(size_t l = 0; l<vec1->size; l++)
    {
        result += vec1->values[l] * vec2->values[l];
    }

    return result;
}



static inline void print_vector(Vector * vec)
{
    printf("[");
    for(size_t i = 0; i < vec->size;i++)
        printf("%f ", vec->values[i]);
    printf("]");
}
static inline void print_vec(double * vec, size_t size)
{
    printf("[");
    for(size_t i = 0; i < size; i++)
        printf("%f ", vec[i]);
    printf("]");
}

static inline void vecm_vec_cprod(double * vec1, double * vec2, double * result)
{

    double * val1 = vec1;
    double * val2 = vec2;
    double valr[3];

    valr[0] = (val1[1] * val2[2]) - (val1[2] * val2[1]);
    valr[1] = (val1[2] * val2[0]) - (val1[0] * val2[2]);
    valr[2] = (val1[0] * val2[1]) - (val1[1] * val2[0]);

    memcpy(result, valr, 3*sizeof(double));
}

static inline void vecm_vec_smult(double * vec, double scalar, double * result, size_t size)
{
    size_t l;
    for(l = 0; l < size; l++)
        result[l] = vec[l] * scalar;
}

static inline void vecm_vec2d_from_deg(double * vec, double angle, double length)
{
    vec[0] = length * cos(vecm_to_rad(angle));
    vec[1] = length * sin(vecm_to_rad(angle));
}
static inline double vecm_vec2d_to_deg(double * vec)
{
    return vecm_to_deg(atan2(vec[1], vec[0]));
};

static inline Matrix * vecm_mat_create(size_t rows, size_t columns)
{
    Matrix * mat = (Matrix*) malloc(sizeof(Matrix));
    mat->rows   = rows;
    mat->columns = columns;
    mat->size   = rows*columns;
    mat->values = (double *) malloc(sizeof(double)*mat->size);
    return mat;
}

static inline void vecm_mat_destroy(Matrix * mat)
{
    free(mat->values);
    free(mat);
}

static inline void vecm_mat_add(Matrix * mat1, Matrix * mat2, Matrix * result)
{
    if (
            (mat1->rows != mat2->rows) || (mat1->rows != result->rows) ||
            (mat1->columns != mat2->columns) || (mat1->columns != result->columns)
       )
    {
        exit(1); //error, matrices are not of the same size
    }
    size_t l;
    for (l = 0; l<mat1->size; l++){ result->values[l] = mat1->values[l] + mat2->values[l]; }
}

static inline void vecm_mat_fill(Matrix * mat, double value)
{
    size_t l;
    for (l = 0; l<mat->size; l++){ mat->values[l] = value; }
}

static inline void vecm_mat_setat(Matrix * mat, size_t row, size_t column, double value)
{
    size_t l = column*mat->rows + row;
    mat->values[l] = value;
}

static inline void print_matrix(Matrix * mat)
{
    size_t c, r, l;
    for(c = 0; c<mat->columns; c++)
    {
        for(r = 0; r<mat->rows; r++)
        {
            l = c*mat->rows + r;
            printf("%f, ", mat->values[l]);
        }
        printf("\n");
    }
}

#endif
