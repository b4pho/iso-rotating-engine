#include <SDL2/SDL.h>
#include <stdbool.h>


#include "ui/sdl_gfx.h"
#include "ui/model.h"

int main(int n, char** args) {
    SDL_Window* window = NULL;
    //SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
                "testc-sdl2",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
                );

    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
    
    Point3D axis = p3d_create(0, 0, 1);
    FaceSet fset = faceset_create();
    model_create(fset);
    Light l = light_create(0, 1000, 0, 1000, color_create(255, 255, 255, 255));
    Point3D camera = p3d_create(1000, 1000, 1000);
    Quaternion rotation = p3d_quat_rotation(axis, 1);
    
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_clear(s);
        SDL_SetRenderDrawBlendMode(s, SDL_BLENDMODE_BLEND);
        show_axis(s, 1000);
        model_render(s, rotation, l, camera, fset);
        SDL_RenderPresent(s);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    quat_destroy(rotation);
    p3d_destroy(camera);
    p3d_destroy(axis);
    light_destroy(l);
    faceset_destroy(fset);
    return 0;
}