#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include "direction.h"

typedef struct Vec2 {
    float x, y;
} Vec2;

typedef struct Vec4 {
    float r, g, b, a;
} Vec4;

bool vec4_is_empty(Vec4 vec);

Vec2 vec2_add_direction(Vec2 vec, Directions dir);

#endif