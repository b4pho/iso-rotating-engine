#include "face.h"

Face face_create(Point3D a, Point3D b, Point3D c, Point3D d, Color color) {
    Face f = (Face) malloc( sizeof(FaceStruct) );
    if ( f == NULL ) {
        printf("face-creation: memory limit reached!");
        exit(-1);
    };
    f -> a = a;
    f -> b = b;
    f -> c = c;
    f -> d = d;
    f -> color = color_create(color -> r, color -> g, color -> b, color -> a);
    f -> center = p3d_create(0, 0, 0);
    face_calculate_center(f);
    f -> index = 0;
    f -> marked = false;
    return f;
}

void face_calculate_center(Face f) {
    f -> center -> x = ( f -> a -> x + f -> b -> x + f -> c -> x + f -> d -> x ) / 4;
    f -> center -> y = ( f -> a -> y + f -> b -> y + f -> c -> y + f -> d -> y ) / 4;
    f -> center -> z = ( f -> a -> z + f -> b -> z + f -> c -> z + f -> d -> z ) / 4;
}

bool face_equals(Face f1, Face f2) {
    return  p3d_equals(f1 -> a, f2 -> a) &&
            p3d_equals(f1 -> b, f2 -> b) &&
            p3d_equals(f1 -> c, f2 -> c) &&
            p3d_equals(f1 -> d, f2 -> d);
}

bool face_x_parallel(Face f1, Face f2) {
    return  p3d_x_parallel(f1 -> a, f2 -> a) &&
            p3d_x_parallel(f1 -> b, f2 -> b) &&
            p3d_x_parallel(f1 -> c, f2 -> c) &&
            p3d_x_parallel(f1 -> d, f2 -> d);
}

bool face_y_parallel(Face f1, Face f2) {
    return  p3d_y_parallel(f1 -> a, f2 -> a) &&
            p3d_y_parallel(f1 -> b, f2 -> b) &&
            p3d_y_parallel(f1 -> c, f2 -> c) &&
            p3d_y_parallel(f1 -> d, f2 -> d);
}

bool face_z_parallel(Face f1, Face f2) {
    return  p3d_z_parallel(f1 -> a, f2 -> a) &&
            p3d_z_parallel(f1 -> b, f2 -> b) &&
            p3d_z_parallel(f1 -> c, f2 -> c) &&
            p3d_z_parallel(f1 -> d, f2 -> d);
}

plane face_plane(Face face) {
    bool is_plane_yz =  face -> a -> x == face -> b -> x && 
                        face -> a -> x == face -> c -> x && 
                        face -> a -> x == face -> d -> x;
    bool is_plane_xy =  face -> a -> z == face -> b -> z && 
                        face -> a -> z == face -> c -> z && 
                        face -> a -> z == face -> d -> z;
    return is_plane_yz ? PLANE_YZ : is_plane_xy ? PLANE_XY : PLANE_XZ;
}

parallel_axis face_parallel(Face f1, Face f2) {
    return  face_x_parallel(f1, f2) ? AXIS_X : 
            face_y_parallel(f1, f2) ? AXIS_Y : 
            face_z_parallel(f1, f2) ? AXIS_Z : NOT_PARALLEL;
}

void face_print(Face face) {
    p3d_print(face -> a);
    p3d_print(face -> b);
    p3d_print(face -> c);
    p3d_print(face -> d);
    color_print(face -> color);
    printf("index: %lf\n\n", face -> index);
}

void face_destroy(Face face)  {
    p3d_destroy(face -> a);
    p3d_destroy(face -> b);
    p3d_destroy(face -> c);
    p3d_destroy(face -> d);
    p3d_destroy(face -> center);
    color_destroy(face -> color);
    free(face);
}