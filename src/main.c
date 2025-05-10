#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "program.h"

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