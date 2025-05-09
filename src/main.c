#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
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
    if (!init_program()) {
        quit_program();
        return 1;
    }

    while (!should_quit()) {
        tick();

        render();
    }

    quit_program();
}