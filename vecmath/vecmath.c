#include "vecmath.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// helper code

double to_rad(double deg)
{
    return deg * 3.14159 / 180.0;
}

/* Vector code */

Vector * vecm_vector_create(size_t size)
{
    Vector * vec = (Vector *) malloc(sizeof(Vector));
    vec->size = size;
    vec->values = (double*) malloc(size * sizeof(double));
    return vec;
}

void vecm_vector_init(Vector * vec, size_t size, double values)
{
    vec->size = size;
    vec->values = (double*) malloc(size * sizeof(double));
    memset(vec->values, values, vec->size);
}

void vecm_vector_destroy(Vector * vec)
{
    free(vec->values);
    free(vec);
}

void vecm_vector_set(Vector * vec, const double * values)
{
    memcpy((void*) vec->values, (void*) values, vec->size*sizeof(double));
}

void vecm_vector_add(Vector * vec1, Vector * vec2, Vector * result)
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

double vecm_vector_dprod(Vector * vec1, Vector * vec2)
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

void vecm_vector_cprod(Vector * vec1, Vector * vec2, Vector * result)
{
    if ((vec1->size != 3) ||
        (vec2->size != 3) || 
        (result->size != 3))
    {
        exit(1); // vectors don't have the correct size!
    }

    double * val1 = vec1->values;
    double * val2 = vec2->values;
    double valr[3];

    valr[0] = (val1[1] * val2[2]) - (val1[2] * val2[1]);
    valr[1] = (val1[2] * val2[0]) - (val1[0] * val2[2]);
    valr[2] = (val1[0] * val2[1]) - (val1[1] * val2[0]);

    memcpy((void*) result->values, (void*) valr, 3*sizeof(double));
}

void vecm_vector_smult(Vector * vec, double scalar, Vector * result)
{
    size_t l;
    for(l = 0; l < vec->size; l++)
        result->values[l] = vec->values[l]*scalar;
}

void vecm_vector_sdiv(Vector * vec, double scalar, Vector * result)
{
    size_t l;
    for(l = 0; l < vec->size; l++)
        result->values[l] = vec->values[l] * scalar;
}

double vecm_vector_len(Vector * vec)
{
    size_t l;
    double result = 0;
    for(l = 0; l<vec->size; l++)
        result += (vec->values[l] * vec->values[l]);
    return sqrt(result);
}

void vecm_vector_from_deg(Vector * vec, double angle, double length)
{
    vec->values[0] = length * cos(to_rad(angle));
    vec->values[1] = length * sin(to_rad(angle));
}

void print_vector(Vector * vec)
{
    printf("[ ");
    for(size_t l = 0; l < vec->size-1; l++){
        printf("%f, ", vec->values[l]);
    }
    printf("%f ]", vec->values[vec->size-1]);
}

/* Matrix code */

Matrix * vecm_mat_create(size_t rows, size_t columns)
{
    Matrix * mat = malloc(sizeof(Matrix));
    mat->rows   = rows;
    mat->columns = columns;
    mat->size   = rows*columns;
    mat->values = malloc(sizeof(double)*mat->size);
    return mat;
}

void vecm_mat_destroy(Matrix * mat)
{
    free(mat->values);
    free(mat);
}

void vecm_mat_add(Matrix * mat1, Matrix * mat2, Matrix * result)
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

void vecm_mat_fill(Matrix * mat, double value)
{
    size_t l;
    for (l = 0; l<mat->size; l++){ mat->values[l] = value; }
}

void vecm_mat_setat(Matrix * mat, size_t row, size_t column, double value)
{
    size_t l = column*mat->rows + row;
    mat->values[l] = value;
}

void print_matrix(Matrix * mat)
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
