#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game_state.h"
#include "program.h"

#define WINDOW_PIXEL_WIDTH 1920
#define WINDOW_PIXEL_HEIGHT 1080

bool should_quit(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                return true;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return true;
                }
            }
        }
    }

    return false;   
}

int main(void) {
    GameState *gameState = malloc(sizeof(GameState));
    gameState->screen_width = WINDOW_PIXEL_WIDTH;
    gameState->screen_height = WINDOW_PIXEL_HEIGHT;
    
    if (!init_program(gameState)) {
        quit_program(gameState);
        return 1;
    }

    while (!should_quit()) {
        tick(gameState);

        render(gameState);
    }

    quit_program(gameState);
}