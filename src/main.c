#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "program.h"

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

    save_image();

    quit_program();
}