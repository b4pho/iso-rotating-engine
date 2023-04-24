#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "face.h"

#ifndef FACESET_HEADER
#define FACESET_HEADER

#define INITIAL_SURFACE_LIMIT 1000

struct FaceSetStruct {
    Face* array;
    int size;
    int max_size;
} FaceSetStruct;

typedef struct FaceSetStruct* FaceSet;

FaceSet faceset_create();

// TODO: PRIVATE? 
void faceset_resize(FaceSet fset, int newSize);

void faceset_addFace(FaceSet fset, Face face);

int faceset_calculateIndexes(FaceSet fset, Point3D p);

void faceset_bubblesort(FaceSet fset, Point3D p);

void faceset_merge(FaceSet fset, Point3D p, int left, int center, int right);

void faceset_mergesort(FaceSet fset, Point3D p, int left, int right);

void faceset_countingsort(FaceSet fset, Point3D p, int k);

void faceset_sort(FaceSet fset, Point3D p);

void faceset_rotate(FaceSet fset, Quaternion rotation);

void faceset_print(FaceSet fset);

void faceset_clear(FaceSet fset);

void faceset_destroy(FaceSet fset);

#endif