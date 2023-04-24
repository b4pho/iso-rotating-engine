#include "color.h"

Color color_create(int r, int g, int b, int a) {
    Color c = (Color) malloc( sizeof(ColorStruct) );
    if ( c == NULL ) {
        printf("color-creation: memory limit reached!");
        exit(-1);
    } 
    c -> r = r;
    c -> g = g;
    c -> b = b;
    c -> a = a;
    return c;
}

Color color_multiply(Color c, double n) {
    return color_create(c -> r * n, c -> g * n, c -> b * n, c -> a);
}

Color color_add(Color c, double n) {
    return color_create(c -> r + n, c -> g + n, c -> b + n, c -> a);
}

bool color_equals(Color c1, Color c2) {
    return  c1 -> r == c2 -> r &&
            c1 -> g == c2 -> g &&
            c1 -> b == c2 -> b &&
            c1 -> a == c2 -> a;
}

void color_print(Color c) {
    printf("(R: %u, G: %u, B: %u, ALPHA: %u)\n", c -> r, c -> g, c -> b, c -> a);
}

void color_destroy(Color c) {
    free(c);
}