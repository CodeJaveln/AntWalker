#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>
#include "vector.h"
#include "stack_vec2.h"

typedef struct GameState {
    int screen_width;
    int screen_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    Vec4 *color_array;
    StackVec2 *stack;
} GameState;

#endif