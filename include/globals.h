#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include "vector.h"
#include "stack_vec2.h"

typedef struct Globals {
    int screen_width;
    int screen_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Vec4 *color_array;
    StackVec2 *stack;
} Globals;

#endif