#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../iso/faceset.h"
#include "../iso/light.h"
#include "sdl_gfx.h"

#ifndef MODEL_HEADER
#define MODEL_HEADER

void model_create(FaceSet fset);

void model_render(SDL_Renderer* s, Quaternion rotation, Light l, Point3D camera, FaceSet fset);

#endif