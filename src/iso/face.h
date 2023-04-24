#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../iso/point3d.h"
#include "color.h"

#ifndef FACE_HEADER
#define FACE_HEADER

#define NOT_PARALLEL    0
#define AXIS_X          1
#define AXIS_Y          2
#define AXIS_Z          3

#define PLANE_XY          1
#define PLANE_XZ          2
#define PLANE_YZ          3

struct FaceStruct {
    Point3D a;
    Point3D b;
    Point3D c;
    Point3D d;
    Point3D center;
    Color color;
    double index;
    bool marked;
} FaceStruct;

typedef struct FaceStruct* Face;

typedef int parallel_axis;

typedef int plane;

Face face_create(Point3D a, Point3D b, Point3D c, Point3D d, Color color);

void face_calculate_center(Face f);

bool face_equals(Face f1, Face f2);

bool face_x_parallel(Face f1, Face f2);

bool face_y_parallel(Face f1, Face f2);

bool face_z_parallel(Face f1, Face f2);

parallel_axis face_parallel(Face f1, Face f2);

plane face_plane(Face face);

void face_print(Face face);

void face_destroy(Face face);

#endif