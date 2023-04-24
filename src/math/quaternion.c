#include "quaternion.h"

Quaternion quat_create(double a, double b, double c, double d) {
    Quaternion q = (Quaternion) malloc( sizeof(QuaternionStruct) );
    if ( q == NULL ) {
        printf("quaternion-creation: memory limit reached!");
        exit(-1);
    } 
    q -> a = a;
    q -> b = b;
    q -> c = c;
    q -> d = d;
    return q;
}

Quaternion quat_multiply(Quaternion q, Quaternion p) {
    Quaternion qp = quat_create(0, 0, 0, 0);
    qp -> a = q -> a * p -> a - q -> b * p -> b - q -> c * p -> c - q -> d * p -> d;
    qp -> b = q -> a * p -> b + q -> b * p -> a + q -> c * p -> d - q -> d * p -> c;
    qp -> c = q -> a * p -> c - q -> b * p -> d + q -> c * p -> a + q -> d * p -> b;
    qp -> d = q -> a * p -> d + q -> b * p -> c - q -> c * p -> b + q -> d * p -> a;
    return qp;
}

Quaternion quat_coniugate(Quaternion q) {
    Quaternion qq = quat_create(0, 0, 0, 0);
    qq -> a = q -> a;
    qq -> b = - q -> b;
    qq -> c = - q -> c;
    qq -> d = - q -> d;
    return qq;
}

void quat_print(Quaternion q) {
    printf("%.2lf %.2lf i %.2lf j %.2lf k\n", q -> a, q -> b, q -> c, q -> d);
}

void quat_destroy(Quaternion q) {
    free(q);
}