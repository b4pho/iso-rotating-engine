#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../math/quaternion.h"
#include "point2d.h"

#ifndef POINT3D_HEADER
#define POINT3D_HEADER

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

struct Point3DStruct {
    double x;
    double y;
    double z;
} Point3DStruct;

typedef struct Point3DStruct* Point3D;

Point3D p3d_create(double x, double y, double z);

double p3d_manhattan_distance(Point3D a, Point3D b);

double p3d_squared_distance(Point3D a, Point3D b);

double p3d_distance(Point3D a, Point3D b);

bool p3d_x_parallel(Point3D p1, Point3D p2);

bool p3d_y_parallel(Point3D p1, Point3D p2);

bool p3d_z_parallel(Point3D p1, Point3D p2);

Point2D p3d_project(Point3D p, double x0, double y0);

Point2D p3d_project0(Point3D p);

Point3D p3d_rotate_by_quat(Point3D p, Quaternion q);

Quaternion p3d_quat_rotation(Point3D axis, double tetha);

Point3D p3d_rotate(Point3D p, Point3D axis, double tetha);

bool p3d_equals(Point3D p1, Point3D p2);

void p3d_print(Point3D p);

void p3d_destroy(Point3D p);

#endif