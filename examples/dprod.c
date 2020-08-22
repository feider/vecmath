#include "../vecmath/vecmath.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main()
{
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
    double dprod = vecm_vector_dprod(a, b);
    printf("dprod: %f\n", dprod);

    vecm_vector_destroy(a);
    vecm_vector_destroy(b);

    /* Timing test */
    a = vecm_vector_create(100);
    b = vecm_vector_create(100);

    clock_t start, end;
    double time_used;
    double result;

    start = clock();
    for(size_t i = 0; i < 1000000; i++)
    {
        result = vecm_vector_dprod(a, b);
    }
    end = clock();
    time_used = ((double) (end-start))/CLOCKS_PER_SEC;

    double ps = (60.0/time_used) * 1000000.0;
    printf("1,000,000 dot products took %f seconds\n", time_used);
    printf("That means %f dot products per second\n", ps);
    vecm_vector_destroy(a);
    vecm_vector_destroy(b);

    return 0;
}
