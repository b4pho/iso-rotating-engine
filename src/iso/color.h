#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef COLOR_HEADER
#define COLOR_HEADER

struct ColorStruct {
    int r;
    int g;
    int b;
    int a;
} ColorStruct;

typedef struct ColorStruct* Color;

Color color_create(int r, int g, int b, int a);

Color color_multiply(Color c, double n);

Color color_add(Color c, double n);

bool color_equals(Color c1, Color c2);

void color_print(Color c);

void color_destroy(Color c);

#endif