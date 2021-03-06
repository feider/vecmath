
#include "../vecmath/vecmath.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    Vector * a = vecm_vector_create(2);
    
    {
        double vals[] = {10, 20};
        vecm_vector_set(a, vals);
    }

    print_vector(a);
    printf("\n");

    vecm_vec_sdiv(a->values, 10, a->values, a->size);

    print_vector(a);
    printf("\n");
    
    vecm_vec_smult(a->values, -1, a->values, a->size);
    print_vector(a);
    printf("\n");
    double len;
    len = vecm_vec_len(a->values, 2);
    printf("vector has len %f\n", len);
    vecm_vec_sdiv(a->values, len, a->values, a->size);
    print_vector(a);
    printf("\n");
    len = vecm_vec_len(a->values, a->size);
    printf("vector has len %f\n", len);

    vecm_vector_destroy(a);
    /* Timing test */
    a = vecm_vector_create(100);

    clock_t start, end;
    double time_used;


    start = clock();
    for(size_t i = 0; i < 1000000; i++)
    {
        vecm_vec_smult(a->values, -2, a->values, a->size);
        len = vecm_vec_len(a->values, a->size);
        vecm_vec_sdiv(a->values, len, a->values, a->size);
    }
    end = clock();
    time_used = ((double) (end-start))/CLOCKS_PER_SEC;

    double ps = (60.0/time_used) * 1000000.0;
    printf("1,000,000 mult, len, div took %f seconds\n", time_used);
    printf("That means %f mult, len, div per second\n", ps);
    vecm_vector_destroy(a);

    return 0;
}
