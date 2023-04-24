#include <stdio.h>
#include <stdlib.h>

#ifndef POINT2D_HEADER
#define POINT2D_HEADER

struct Point2DStruct {
    double x;
    double y;
} Point2DStruct;

typedef struct Point2DStruct* Point2D;

Point2D p2d_create(double x, double y);

void p2d_print(Point2D p);

void p2d_destroy(Point2D p);

#endif