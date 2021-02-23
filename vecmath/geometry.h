#ifndef GEOMETRY_H
#define GEOMETRY_H

/*
void fdrm_points_to_line(const double * points, double * line);
int fdrm_lines_intersect(const double * line_1, const double * line_2, double * point);
int fdrm_segments_intersect(const double * points_1, const double * points_2, double * point_intersection);
int fdrm_point_in_segment(const double * point, const double * segment);
void fdrm_seg_from_points(const double * p1, const double * p2, double * segment);
double fdrm_side(const double * segment, const double * point);
*/


// implementation
#include <math.h>
#include <string.h>

static inline void fdrm_points_to_line(const double * points, double * line)
{
    double x1 = points[0];
    double y1 = points[1];
    double x2 = points[2];
    double y2 = points[3];
    line[0] = y1-y2;
    line[1] = x2-x1;
    line[2] = (x2*y1) - (x1*y2);
}

static inline int fdrm_lines_intersect(const double * line_1, const double * line_2, double * point)
{
    double a1 = line_1[0];
    double b1 = line_1[1];
    double c1 = line_1[2];
    double a2 = line_2[0];
    double b2 = line_2[1];
    double c2 = line_2[2];

    double d = (a1*b2) - (a2*b1);

    point[0] = ( (c1*b2) - (c2*b1) ) / ( d );
    point[1] = ( (a1*c2) - (a2*c1) ) / ( d );
    
    return (d != 0);
}

static inline int fdrm_point_in_segment(const double * point, const double * segment)
{
    const double * sp1 = segment;
    const double * sp2 = segment+2;

    const double d[2] = {sp2[0]-sp1[0], sp2[1]-sp1[1]};

    if (fabs(d[0]) >= fabs(d[1]))
        return d[0] > 0 ?
            sp1[0] <= point[0] && point[0] <= sp2[0] :
            sp2[0] <= point[0] && point[0] <= sp1[0] ;
    else
        return d[1] > 0 ?
            sp1[1] <= point[1] && point[1] <= sp2[1] :
            sp2[1] <= point[1] && point[1] <= sp1[1] ;



}

static inline int fdrm_segments_intersect(const double * points_1, const double * points_2, double * point_intersection)
{
    double * pi = point_intersection;
    // first get intersection point
    double l1[3], l2[3];
    fdrm_points_to_line(points_1, l1);
    fdrm_points_to_line(points_2, l2);
    int not_parallel = fdrm_lines_intersect(l1, l2, pi);

    // lines are parallel, return
    if(not_parallel == 0) return 0;

    // if lines are not parallel, check if poit is between points
    return (fdrm_point_in_segment(pi, points_1) && fdrm_point_in_segment(pi, points_2));
}

static inline void fdrm_seg_from_points(const double * p1, const double * p2, double * segment)
{
    memcpy(segment, p1, 2*sizeof(double));
    memcpy(segment+2, p2, 2*sizeof(double));
}

static inline double fdrm_side(const double * segment, const double * point)
{
    double l[3];
    fdrm_points_to_line(segment, l);
    return (l[0] * point[0]) + (l[1]*point[1]) + l[2];
}

static inline double fdrm_point_segment_distance(const double * segment, const double * point)
{
    double l[3];
    fdrm_points_to_line(segment, l);
    return fabs( 
              (l[0] * point[0]) 
            + (l[1] * point[1]) 
            -  l[2]) / 
        sqrt(
                  (l[0] * l[0]) 
                + (l[1] * l[1])
                );
}

#endif
