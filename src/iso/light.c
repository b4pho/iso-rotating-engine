#include "light.h"

Light light_create(double x, double y, double z, double radius, Color c) {
    Light light  = (Light) malloc( sizeof(LightStruct) );
    if ( light == NULL ) {
        printf("light-creation: memory limit reached!");
        exit(-1);
    } 
    light -> origin = p3d_create(x, y, z);
    light -> radius = radius;
    light -> color = c;
    return light;
}

Color light_color(Light light, Point3D p, Color c, double intensity) {
    double r2 = light -> radius * light -> radius;
    double d2 = p3d_squared_distance(light -> origin, p);
    double factor = d2 < r2 ? (r2 - d2) / r2 : 0;
    int r = (light -> color -> r * factor * 2 * intensity + c -> r * (2 - (2 * intensity) ) ) / 2;
    int g = (light -> color -> g * factor * 2 * intensity + c -> g * (2 - (2 * intensity) ) ) / 2;
    int b = (light -> color -> b * factor * 2 * intensity + c -> b * (2 - (2 * intensity) ) ) / 2;
    return color_create(r, g, b, c -> a);
}

void light_destroy(Light light) {
    p3d_destroy(light -> origin);
    color_destroy(light -> color);
    free(light);
}