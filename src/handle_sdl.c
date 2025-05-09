#include "handle_sdl.h"

#include <SDL2/SDL.h>
#include "program.h"

bool init_sdl(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error, can't initialize SDL!");
        quit_sdl(*window, *renderer);
        return false;
    }
    
    *window = SDL_CreateWindow("Ant Walker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, get_globals()->screen_width, get_globals()->screen_height, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
    if (*window == NULL) {
        fprintf(stderr, "Couldn't initialize window, SDL_GetError: %s\n", SDL_GetError());
        quit_sdl(*window, *renderer);
        return false;
    }
    
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        fprintf(stderr, "Couldn't initialize renderer, SDL_GetError: %s\n", SDL_GetError());
        quit_sdl(*window, *renderer);
        return false;
    }

    return true;
}

void quit_sdl(SDL_Window *window, SDL_Renderer *renderer) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != NULL) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}