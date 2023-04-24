#include "point3d.h"

Point3D p3d_create(double x, double y, double z) {
    Point3D p = (Point3D) malloc( sizeof(Point3DStruct) );
    if ( p == NULL ) {
        printf("point-3d-creation: memory limit reached!");
        exit(-1);
    } 
    p -> x = x;
    p -> y = y;
    p -> z = z;
    return p;
}

double p3d_manhattan_distance(Point3D a, Point3D b) {
    double dx = a -> x > b -> x ? a -> x - b -> x : b -> x - a -> x;
    double dy = a -> y > b -> y ? a -> y - b -> y : b -> y - a -> y;
    double dz = a -> z > b -> z ? a -> z - b -> z : b -> z - a -> z;
    return dx + dy + dz;
}

double p3d_squared_distance(Point3D a, Point3D b) {
    double dx = a -> x - b -> x;
    double dy = a -> y - b -> y;
    double dz = a -> z - b -> z;
    return dx * dx + dy * dy + dz * dz;
}

double p3d_distance(Point3D a, Point3D b) {
    double dx = a -> x - b -> x;
    double dy = a -> y - b -> y;
    double dz = a -> z - b -> z;
    return hypot(dx, hypot(dy, dz));
}

Point2D p3d_project(Point3D p, double x0, double y0) {
    double xx = p -> x - p -> z;
    double yy = p -> x * 0.5 - p -> y + p -> z * 0.5;
    return p2d_create(xx + x0, yy + y0);
}

Point2D p3d_project0(Point3D p) {
    return p3d_project(p, 0, 0);
}

Point3D p3d_rotate_by_quat(Point3D p, Quaternion q) {
    Quaternion pp = quat_create(0, p -> x, p -> y, p -> z);
    Quaternion qpp = quat_multiply(q, pp);
    Quaternion qq = quat_coniugate(q);
    Quaternion result = quat_multiply(qpp, qq);
    Point3D p2 = p3d_create(result -> b, result -> c, result -> d);
    quat_destroy(pp);
    quat_destroy(qpp);
    quat_destroy(qq);
    quat_destroy(result);
    return p2;
}

Quaternion p3d_quat_rotation(Point3D axis, double tetha) {
    double radians = degToRad(tetha);
    double c = cos(radians * 0.5);
    double s = sin(radians * 0.5);
    return quat_create(c, axis -> x * s, axis -> y * s, axis -> z * s);
}

Point3D p3d_rotate(Point3D p, Point3D axis, double tetha) {
    Quaternion q = p3d_quat_rotation(axis, tetha);
    Point3D p2 = p3d_rotate_by_quat(p, q);
    quat_destroy(q);
    return p2;
}

bool p3d_equals(Point3D p1, Point3D p2) {
    return  p1 -> x == p2 -> x &&
            p1 -> y == p2 -> y &&
            p1 -> z == p2 -> z;
}

void p3d_print(Point3D p) {
    printf("(%.2lf, %.2lf, %.2lf)\n", p -> x, p -> y, p -> z);
}

bool p3d_x_parallel(Point3D p1, Point3D p2) {
    return  p1 -> x != p2 -> x &&
            p1 -> y == p2 -> y && 
            p1 -> z == p2 -> z;
}

bool p3d_y_parallel(Point3D p1, Point3D p2) {
    return  p1 -> x == p2 -> x &&
            p1 -> y != p2 -> y && 
            p1 -> z == p2 -> z;
}

bool p3d_z_parallel(Point3D p1, Point3D p2) {
    return  p1 -> x == p2 -> x &&
            p1 -> y == p2 -> y && 
            p1 -> z != p2 -> z;
}

void p3d_destroy(Point3D p) {
    free(p);
}