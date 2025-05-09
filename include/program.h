#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>
#include "game_state.h"

bool init_program(GameState *gameState);

void quit_program(GameState *gameState);

void tick(GameState *gameState);

void render(GameState *gameState);

#endif