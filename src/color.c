#include "color.h"

#include "math_helper.h"
#include "random.h"

Vec4 random_col(void) {
    Vec4 vec;
    vec.r = randf(0, 1.0f);
    vec.g = randf(0, 1.0f);
    vec.b = randf(0, 1.0f);
    vec.a = 1.0f;
    return vec;    
}

Vec4 generate_col(Vec4 seed) {
    Vec4 vec;
    vec.r = math_clampf(randf(-0.005f, 0.005f) + seed.r, 0, 1.0f);
    vec.g = math_clampf(randf(-0.005f, 0.005f) + seed.g, 0, 1.0f);
    vec.b = math_clampf(randf(-0.005f, 0.005f) + seed.b, 0, 1.0f);
    vec.a = 1.0f;
    
    return vec;
}

SDL_Color vec4_to_col(Vec4 vec) {
    SDL_Color col;
    col.r = (int)(255.0f * vec.r);
    col.g = (int)(255.0f * vec.g);
    col.b = (int)(255.0f * vec.b);
    col.a = (int)(255.0f * vec.a);

    return col;
}