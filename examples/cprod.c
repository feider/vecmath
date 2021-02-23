#include "../vecmath/vecmath.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    Vector * a = vecm_vector_create(3);
    Vector * b = vecm_vector_create(3);
    Vector * c = vecm_vector_create(3);
    
    {
        double vals[] = {1, 0, 0};
        vecm_vector_set(a, vals);
    }
    {
        double vals[] = {0, 1, 0};
        vecm_vector_set(b, vals);
    }

    vecm_vec_cprod(a->values, b->values, c->values);


    print_vector(a);
    printf("\n");
    print_vector(b);
    printf("\n");
    print_vector(c);
    printf("\n");



    /* Timing test */

    {
        double vals[] = {1, 2, 0.3};
        vecm_vector_set(a, vals);
    }
    {
        double vals[] = {0.1, -2, 5};
        vecm_vector_set(b, vals);
    }

    clock_t start, end;
    double time_used;
    double result;

    start = clock();
    for(size_t i = 0; i < 1000000; i++)
    {
        vecm_vec_cprod(a->values, b->values, c->values);
    }
    end = clock();
    time_used = ((double) (end-start))/CLOCKS_PER_SEC;

    double ps = (60.0/time_used) * 1000000.0;
    printf("1,000,000 cross products took %f seconds\n", time_used);
    printf("That means %f cross products per second\n", ps);

    vecm_vector_destroy(a);
    vecm_vector_destroy(b);
    vecm_vector_destroy(c);

    return 0;
}
