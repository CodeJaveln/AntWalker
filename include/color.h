#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include "vector.h"

Vec4 random_col(void);

Vec4 generate_col(Vec4 seed, float mod_min, float mod_max);

SDL_Color vec4_to_col(Vec4 vec);

#endif