#include <stdio.h>
#include <stdlib.h>

#include "../iso/point3d.h"
#include "color.h"

#ifndef LIGHT_HEADER
#define LIGHT_HEADER


struct LightStruct {
    Point3D origin;
    double radius;
    Color color;
} LightStruct;

typedef struct LightStruct* Light;

Light light_create(double x, double y, double z, double radius, Color c);

Color light_color(Light light, Point3D p, Color c, double intensity);

void light_destroy(Light light);

#endif