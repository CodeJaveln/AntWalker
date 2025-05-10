#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>
#include "globals.h"

Globals *get_globals(void);

bool init_program(void);

void quit_program(void);

void tick(void);

void render(void);

void save_image(void);

bool should_quit(void);

#endif