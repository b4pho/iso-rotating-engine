#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "../iso/faceset.h"
#include "../iso/light.h"

#ifndef SDL_GFX_HEADER
#define SDL_GFX_HEADER

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

double min(double a, double b);

double max(double a, double b);

void SDL_clear(SDL_Renderer* s);

void SDL_pixel(SDL_Renderer* s, int x, int y, Color c);

void SDL_line(SDL_Renderer* s, int x1, int y1, int x2, int y2, Color c);

void SDL_3D_point(SDL_Renderer* s, Point3D p, Color c);

void SDL_3D_pixel(SDL_Renderer* s, int x, int y, int z, Color c);

void SDL_generate_cube(FaceSet sset, int x, int y, int z, int size, Color colors[]);

void SDL_fill_face(SDL_Renderer* s, Face face, Light l);

void SDL_draw_surface(SDL_Renderer* s, FaceSet fset, Light l);

void show_axis(SDL_Renderer* s, int size);

#endif