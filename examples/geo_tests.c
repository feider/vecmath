#include <stdio.h>
#include <vecmath/geometry.h>
#include <time.h>

int main(int argc, char ** argv){

    double seg1[4] = {-1, -1, 2, 2};
    double seg2[4] = {2, 0, 0, 2};
    double seg3[4] = {3, 1, 3, 3};
    double seg4[4];
    {
        double p1[2] = {1, -3};
        double p2[2] = {3, -1};
        fdrm_seg_from_points(p1, p2, seg4);
    }

    double line1[3], line2[3], line3[3], line4[3];

    fdrm_points_to_line(seg1, line1);
    fdrm_points_to_line(seg2, line2);
    fdrm_points_to_line(seg3, line3);
    fdrm_points_to_line(seg4, line4);

    double intersection[2];
    int inter;

    printf("\n\n\nintersect 1 and 2\n");
    inter = fdrm_lines_intersect(line1, line2, intersection);
    printf("line intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);
    inter = fdrm_segments_intersect(seg1, seg2, intersection);
    printf("point intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);

    printf("\n\n\nintersect 1 and 3\n");
    inter = fdrm_lines_intersect(line1, line3, intersection);
    printf("line intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);
    inter = fdrm_segments_intersect(seg1, seg3, intersection);
    printf("point intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);

    printf("\n\n\nintersect 2 and 3\n");
    inter = fdrm_lines_intersect(line2, line3, intersection);
    printf("line intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);
    inter = fdrm_segments_intersect(seg2, seg3, intersection);
    printf("point intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);

    printf("\n\n\nintersect 1 and 4\n");
    inter = fdrm_lines_intersect(line1, line4, intersection);
    printf("line intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);
    inter = fdrm_segments_intersect(seg1, seg4, intersection);
    printf("point intersection at %f, %f, truth: %d\n", intersection[0], intersection[1], inter);

    {
        clock_t start, end;
        double time_used;
        start = clock();
        for(size_t i = 0; i<1000000; i++)
        {
            inter += fdrm_lines_intersect(line1, line3, intersection);
        }
        end = clock();
        time_used = ((double) (end-start))/CLOCKS_PER_SEC;
        double ps = (60.0/time_used) * 1000000.0;
        printf("\n\n\n1,000,000 line intersections took %f seconds\n", time_used);
        printf("That means %f line intersections per second\n", ps);
    }
    {
        clock_t start, end;
        double time_used;
        start = clock();
        for(size_t i = 0; i<1000000; i++)
        {
            inter += fdrm_segments_intersect(seg1, seg2, intersection);
        }
        end = clock();
        time_used = ((double) (end-start))/CLOCKS_PER_SEC;
        double ps = (60.0/time_used) * 1000000.0;
        printf("\n\n\n1,000,000 segment intersections took %f seconds\n", time_used);
        printf("That means %f segment intersections per second\n", ps);
    }








    return 0;
}
