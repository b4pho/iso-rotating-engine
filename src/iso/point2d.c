#include "point2d.h"

Point2D p2d_create(double x, double y) {
    Point2D p = (Point2D) malloc( sizeof(Point2DStruct) );
    if ( p == NULL ) {
        printf("point-2d-creation: memory limit reached!");
        exit(-1);
    } 
    p -> x = x;
    p -> y = y;
    return p;
}

void p2d_print(Point2D p) {
    printf("(%.2lf, %.2lf)\n", p -> x, p -> y);
}

void p2d_destroy(Point2D p) {
    free(p);
}