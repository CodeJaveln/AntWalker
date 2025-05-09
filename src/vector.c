#include "vector.h"

#include <string.h>

bool vec4_is_empty(Vec4 vec) {
    return vec.r + vec.g + vec.b + vec.a == 0;
}

Vec2 vec2_add_direction(Vec2 vec, Directions dir) {
    Vec2 retval = vec;
    switch (dir) {
        case DIR_NORTH: {
            retval.y = vec.y - 1;
            break;
        }
        case DIR_EAST: {
            retval.x = vec.x + 1;
            break;
        }
        case DIR_SOUTH: {
            retval.y = vec.y + 1;
            break;
        }
        case DIR_WEST: {
            retval.x = vec.x - 1;
            break;
        }
    }

    return retval;
}