#include "model.h"

void model_simplify(FaceSet fset);

void model_create(FaceSet fset) {
    Color colors[6] = {
        color_create(0, 0, 255, 255),
        color_create(0, 255, 0, 255),
        color_create(255, 0, 0, 255),
        color_create(0, 255, 255, 255),
        color_create(255, 0, 255, 255),
        color_create(150, 150, 0, 255)
    };  
    
    int sum = 0;
    int size = 20;
    int t, i, j;
    for (t = 0; t < 500; t += size) {
        for (i = t; i < 500 - t; i += size) {
            for (j = t; j < 500 - t; j += size) {
                SDL_generate_cube(fset, i, t, j, size, colors);
                sum++;
            }
        }
    }
    printf("(%d)\n", sum);
    model_simplify(fset);
    for (i = 0; i < 6; i++) {
        color_destroy(colors[i]);
    }
}

void model_render(SDL_Renderer* s, Quaternion rotation, Light l, Point3D camera, FaceSet fset) {
    faceset_rotate(fset, rotation);
    faceset_sort(fset, camera);
    SDL_draw_surface(s, fset, l);
}

void model_mark_useless_x_faces(FaceSet fset, Face* marked_faces, int* num_marks) {
    int i, j;
    int min, max;
    Face minFace;
    Face maxFace;
    for (j = 0; j < fset -> size; j++) {
        Face f1 = fset -> array[j];
        if (f1 -> marked || face_plane(f1) != PLANE_YZ) {
            continue;
        }
        min = f1 -> center -> x;
        max = f1 -> center -> x;
        minFace = f1;
        maxFace = f1;
        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            }
            if ( face_x_parallel(f1, f2) ) {
                if (f2 -> center -> x > max) {
                    max = f2 -> center -> x;
                    maxFace = f2;
                }
                if (f2 -> center -> x < min) {
                    min = f2 -> center -> x;
                    minFace = f2;
                }
            }
        }

        if (minFace == maxFace && minFace == f1) {
            continue;
        }

        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            } 
            double cx = f2 -> center -> x;
            // && f2 != minFace && f2 != maxFace
            // && cx != min && cx != max 
            if ( face_x_parallel(f1, f2) && f2 != minFace && f2 != maxFace ) {
                //marked_faces[*num_marks++] = f2;
                f2 -> marked = true;
                *num_marks = *num_marks + 1;
            }
        }
    }
}

void model_mark_useless_y_faces(FaceSet fset, Face* marked_faces, int* num_marks) {
    int i, j;
    int min, max;
    Face minFace;
    Face maxFace;
    for (j = 0; j < fset -> size; j++) {
        Face f1 = fset -> array[j];
        if (f1 -> marked || face_plane(f1) != PLANE_XZ) {
            continue;
        }
        min = f1 -> center -> y;
        max = f1 -> center -> y;
        minFace = f1;
        maxFace = f1;
        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            }
            if ( face_y_parallel(f1, f2) ) {
                if (f2 -> center -> y > max) {
                    max = f2 -> center -> y;
                    maxFace = f2;
                }
                if (f2 -> center -> y < min) {
                    min = f2 -> center -> y;
                    minFace = f2;
                }
            }
        }

        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            }            
            double cy = f2 -> center -> y;
            if ( face_y_parallel(f1, f2) && cy != min && cy != max ) {
                //marked_faces[*num_marks++] = f2;
                f2 -> marked = true;
                *num_marks = *num_marks + 1;
            }
        }
    }
}

void model_mark_useless_z_faces(FaceSet fset, Face* marked_faces, int* num_marks) {
    int i, j;
    int min, max;
    Face minFace;
    Face maxFace;
    for (j = 0; j < fset -> size; j++) {
        Face f1 = fset -> array[j];
        if (f1 -> marked || face_plane(f1) != PLANE_XY) {
            continue;
        }        
        min = f1 -> center -> z;
        max = f1 -> center -> z;
        minFace = f1;
        maxFace = f1;
        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            }            
            if ( face_z_parallel(f1, f2) ) {
                if (f2 -> center -> z > max) {
                    max = f2 -> center -> z;
                    maxFace = f2;
                }
                if (f2 -> center -> z < min) {
                    min = f2 -> center -> z;
                    minFace = f2;
                }
            }
        }

        for (i = 0; i < fset -> size; i++) {
            Face f2 = fset -> array[i];
            if (f2 -> marked) {
                continue;
            }                
            double cz = f2 -> center -> z;
            if ( face_z_parallel(f1, f2) && cz != min && cz != max ) {
                //marked_faces[*num_marks++] = f2;
                f2 -> marked = true;
                *num_marks = *num_marks + 1;
            }
        }
    }
}

void model_mark_useless_faces(FaceSet fset, Face** marked_faces, int* num_marks) {
    /*bool optimizing = true;
    while (optimizing) {
        optimizing = false;
        Face face = fset -> 
    }*/

    *num_marks = 0;
    /*
    *marked_faces = (Face*) malloc( fset -> size * sizeof(Face));
    if (*marked_faces == NULL) {
        printf("model-simplify-allocation: memory limit reached!");
        exit(-1);        
    }
    */
    model_mark_useless_x_faces(fset, *marked_faces, num_marks);
    printf("after x-faces-optimization, marked: %d\n", *num_marks);
    model_mark_useless_y_faces(fset, *marked_faces, num_marks);
    printf("after y-faces-optimization, marked: %d\n", *num_marks);
    model_mark_useless_z_faces(fset, *marked_faces, num_marks); 
    printf("after z-faces-optimization, marked: %d\n", *num_marks);
}

void model_remove_marked_faces(FaceSet fset, Face* marked_faces, int num_marks) {
    if (num_marks == 0) {
        printf("Nothing left to optimize.\n");
        return;
    }
    printf("current_size: %d, max_size: %d\n", fset -> size, fset -> max_size);
    int new_size = fset -> size - num_marks + 1;
    Face* new_array = (Face*) malloc( new_size * sizeof(Face));
    if (new_array == NULL) {
        printf("model-simplify-allocation: memory limit reached!");
        exit(-1);
    };
    Face* old_array = fset -> array;
    int i, j, t;
    for (i = 0, j = 0; i < fset -> size; i++) {
        Face face = fset -> array[i];
        bool found = false;
        /*
        for (t = 0; t < num_marks; t++) {
            Face marked_face = marked_faces[t];
            if ( face_equals(face, marked_face) ) {
                found = true;
                break;
            }
        } */
        if (face -> marked == true) {
            found = true;
        }
        if (found) {
            face_destroy(face);
        } else {
            new_array[j++] = face;
        }
    } 
    fset -> array = new_array;
    fset -> size = j;
    fset -> max_size = new_size;
    printf("current_size: %d, max_size: %d\n", fset -> size, fset -> max_size);
    free(old_array);    
}

void model_simplify(FaceSet fset) {
    Face* marked_faces = NULL;
    int num_marks = 0;
    printf("Optimizing model...\n");
    do {
        model_mark_useless_faces(fset, &marked_faces, &num_marks);
        model_remove_marked_faces(fset, marked_faces, num_marks);
    } while ( num_marks > 0 );
}
