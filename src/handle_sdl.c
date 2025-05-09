#include "handle_sdl.h"

#include <SDL2/SDL.h>

bool init_sdl(GameState *gameState) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error, can't initialize SDL!");
        quit_sdl(gameState);
        return false;
    }
    
    gameState->window = SDL_CreateWindow("Ant Walker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameState->screen_width, gameState->screen_height, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
    if (gameState->window == NULL) {
        fprintf(stderr, "Couldn't initialize window, SDL_GetError: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    gameState->renderer = SDL_CreateRenderer(gameState->window, -1, SDL_RENDERER_ACCELERATED);
    if (gameState->renderer == NULL) {
        fprintf(stderr, "Couldn't initialize renderer, SDL_GetError: %s\n", SDL_GetError());
        quit_sdl(gameState);
        return false;
    }

    gameState->surface = SDL_CreateRGBSurface(0, gameState->screen_width, gameState->screen_height, 32, 0, 0, 0, 0);

    return true;
}

void quit_sdl(GameState *gameState) {
    if (gameState->renderer != NULL) {
        SDL_DestroyRenderer(gameState->renderer);
    }

    if (gameState->window != NULL) {
        SDL_DestroyWindow(gameState->window);
    }

    SDL_Quit();
}