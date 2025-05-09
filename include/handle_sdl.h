#ifndef HANDLE_SDL_H
#define HANDLE_SDL_H

#include <stdbool.h>
#include "game_state.h"

bool init_sdl(GameState *gameState);

void quit_sdl(GameState *gameState);

#endif