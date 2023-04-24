#include <stdio.h>
#include <stdlib.h>

#ifndef QUATERNION_HEADER
#define QUATERNION_HEADER

struct QuaternionStruct {
    double a;
    double b;
    double c;
    double d;
} QuaternionStruct;

typedef struct QuaternionStruct* Quaternion;

Quaternion quat_create(double a, double b, double c, double d);

Quaternion quat_multiply(Quaternion q, Quaternion p);

Quaternion quat_coniugate(Quaternion q);

void quat_print(Quaternion q);

void quat_destroy(Quaternion q);

#endif
