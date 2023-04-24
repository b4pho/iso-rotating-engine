#include "faceset.h"

FaceSet faceset_create() {
    FaceSet fset = (FaceSet) malloc( sizeof(FaceSetStruct) );
    if ( fset == NULL ) {
        printf("face-set-creation: memory limit reached!");
        exit(-1);
    };
    fset -> size = 0;
    fset -> max_size = INITIAL_SURFACE_LIMIT;
    fset -> array = (Face*) malloc(INITIAL_SURFACE_LIMIT * sizeof(Face));
    if ( fset -> array == NULL ) {
        printf("face-set-stack-allocation: memory limit reached!");
        exit(-1);
    };
    return fset;
}

void faceset_resize(FaceSet fset, int new_size) {
    printf("HIT! new-max-size: %d, current-size-cursor: %d\n", new_size, fset -> size);
    fset-> max_size = new_size;
    fset-> array = (Face*) realloc(fset->array, new_size * sizeof(Face));
    if ( fset -> array == NULL ) {
        printf("face-set-stack-reallocation: memory limit reached!");
        exit(-1);
    };  
}

void faceset_addFace(FaceSet fset, Face face) {
    if (fset -> size == fset -> max_size) {
        faceset_resize(fset, (fset -> max_size) * 2);
    }
    fset -> array[(fset -> size)++] = face;
}

int faceset_calculateIndexes(FaceSet fset, Point3D p) {
    int maxIndex = 0, minIndex = 0;
    bool start = true;
    int i;
    for (i = 0; i < fset -> size; i++) {
        Face face = fset -> array[i];
        int index = (int) p3d_manhattan_distance(face -> center, p);
        if (start) {
            start = false;
            maxIndex = index;
            minIndex = index;
        } else if (maxIndex < index) {
            maxIndex = index;
        } else if (minIndex > index) {
            minIndex = index;
        }
        face -> index = index;
    }
    int count = 0;
    for (i = 0; i < fset -> size; i++) {
        Face face = fset -> array[i];
        face -> index -= minIndex;
        count++;
    }
    maxIndex -= minIndex;
    return maxIndex;   
}

// O(n2) TODO: IMPROVE! --> O(nlogn)
void faceset_bubblesort(FaceSet fset, Point3D p) {
    int i, j;
    bool tochange = true;
    while (tochange) {
        tochange = false;
        for (j = 0; j < fset -> size - 1; j++) { 
            for (i = j + 1; i < fset -> size; i++) {
                Face face1 = fset -> array[j];
                Face face2 = fset -> array[i];
                if (face1 -> index < face2 -> index) {
                        tochange = true;
                        fset -> array[j] = face2;
                        fset -> array[i] = face1;
                }
            }
        }
    }
}

void faceset_merge(FaceSet fset, Point3D p, int left, int center, int right) {
    int i = left;
    int j = center + 1;
    int k = 0;

    Face* temp = (Face*) malloc( (right - left + 1) * sizeof(Face) );
    if ( temp == NULL ) {
        printf("face-mergesort-allocation: memory limit reached!");
        exit(-1);
    };  
    
    while (i <= center && j <= right) {
        if ( (fset -> array[i]) -> index >= (fset-> array[j]) -> index) {
            temp[k] = fset -> array[i++];
        } else {
            temp[k] = fset -> array[j++];
        }
        k++;
    }
    
    while (i <= center) {
        temp[k++] = fset -> array[i++];
    }
    
    while (j <= right) {
        temp[k++] = fset -> array[j++];
    }
    
    for (k = left; k <= right; k++) {
        fset->array[k] = temp[k - left];
    }

    free(temp);
}

// O(nlogn)
void faceset_mergesort(FaceSet fset, Point3D p, int left, int right) {
    if (left < right) {
        int center = ( left + right ) / 2;
        faceset_mergesort(fset, p, left, center);
        faceset_mergesort(fset, p, center + 1, right);
        faceset_merge(fset, p, left, center, right);
    }
}

// O(n)
void faceset_countingsort(FaceSet fset, Point3D p, int k) {
    int* count = (int*) calloc(k + 1, sizeof(int));
    int* pos = (int*) calloc(k + 1, sizeof(int));
    Face** faces = (Face**) calloc(k + 1, sizeof(Face*));
    int i, j, t;
    
    for (i = 0; i < fset -> size; i++) {
        int index = fset -> array[i] -> index;
        count[index]++;
    }

    for (i = 0; i < fset -> size; i++) {
        int index = fset -> array[i] -> index;
        if (faces[index] == NULL) {
            faces[index] = (Face*) calloc(count[index], sizeof(Face));
        }
        faces[index][pos[index]++] = fset -> array[i];
    }

    int x = 0;
    for (i = k, j = 0; i >= 0; i--) {
        for (t = 0; t < pos[i]; t++) {
            fset -> array[j++] = faces[i][t];
            x++;
        }
    }
    free(faces);
    free(count);
    free(pos);
    //printf("count: %d\n", x);
}

void faceset_sort(FaceSet fset, Point3D p) {
    int max = faceset_calculateIndexes(fset, p);
    //faceset_mergesort(fset, p, 0, fset -> size - 1);
    //faceset_bubblesort(fset, p);
    faceset_countingsort(fset, p, max);
}

void faceset_rotate(FaceSet fset, Quaternion rotation) {
    int i;
    for (i = 0; i < fset -> size; i++) {
        Point3D new_a = p3d_rotate_by_quat(fset -> array[i] -> a, rotation);
        Point3D new_b = p3d_rotate_by_quat(fset -> array[i] -> b, rotation);
        Point3D new_c = p3d_rotate_by_quat(fset -> array[i] -> c, rotation);
        Point3D new_d = p3d_rotate_by_quat(fset -> array[i] -> d, rotation);
        p3d_destroy(fset -> array[i] -> a);
        p3d_destroy(fset -> array[i] -> b);
        p3d_destroy(fset -> array[i] -> c);
        p3d_destroy(fset -> array[i] -> d);
        fset -> array[i] -> a =  new_a;
        fset -> array[i] -> b =  new_b;
        fset -> array[i] -> c =  new_c;
        fset -> array[i] -> d =  new_d;
        face_calculate_center(fset -> array[i]);
    }  
}

void faceset_print(FaceSet fset) {
    int i;
    if (fset -> size == 0) {
        printf("<EMPTY>\n");
    }
    for (i = 0; i < fset -> size; i++) {
        face_print(fset -> array[i]);
    }
}

void faceset_clear(FaceSet fset) {
    int i;
    for (i = 0; i < fset -> size; i++) {
        face_destroy(fset -> array[i]);
    }        
    fset -> size = 0;
}

void faceset_destroy(FaceSet fset) {
    faceset_clear(fset);
    free(fset);
}