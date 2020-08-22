#include "../vecmath/vecmath.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    {

    printf("Vector addition\n");

    Vector * a = vecm_vector_create(2);
    Vector * b = vecm_vector_create(2);
    
    {
        double vals[] = {1, 2};
        vecm_vector_set(a, vals);
    }
    {
        double vals[] = {10, -10};
        vecm_vector_set(b, vals);
    }

    print_vector(a);
    printf("\n");
    print_vector(b);
    printf("\n");
    vecm_vector_add(a, b, a);
    print_vector(a);
    printf("\n");
    vecm_vector_destroy(a);
    vecm_vector_destroy(b);


    /* Timing test */
    a = vecm_vector_create(100);
    b = vecm_vector_create(100);

    clock_t start, end;
    double time_used;

    start = clock();
    for(size_t i = 0; i < 1000000; i++)
    {
        vecm_vector_add(a, b, a);
    }
    end = clock();
    time_used = ((double) (end-start))/CLOCKS_PER_SEC;

    double ps = (60.0/time_used) * 1000000.0;
    printf("1,000,000 additions took %f seconds\n", time_used);
    printf("That means %f additions per second\n", ps);
    vecm_vector_destroy(a);
    vecm_vector_destroy(b);

    }

    {

    printf("Matrix addition\n");
    Matrix * a = vecm_mat_create(3, 2);
    vecm_mat_fill(a, 1);
    vecm_mat_setat(a, 1, 1, 0);
    Matrix * b = vecm_mat_create(3, 2);
    vecm_mat_fill(b, 2);
    printf("Matrix a\n");
    print_matrix(a);
    printf("Matrix b\n");
    print_matrix(b);

    vecm_mat_add(a, b, a);
    printf("Sum\n");
    print_matrix(a);

    vecm_mat_destroy(a);
    vecm_mat_destroy(b);

    /* timing test */
    a = vecm_mat_create(10, 10);
    b = vecm_mat_create(10, 10);

    clock_t start, end;
    double time_used;
    start = clock();
    for(size_t i = 0; i<1000000; i++)
    {
        vecm_mat_add(a, b, a);
    }
    end = clock();
    time_used = ((double) (end-start))/CLOCKS_PER_SEC;
    double ps = (60.0/time_used) * 1000000.0;
    printf("1,000,000 additions took %f seconds\n", time_used);
    printf("That means %f additions per second\n", ps);

    vecm_mat_destroy(a);
    vecm_mat_destroy(b);



    }

    return 0;
}

