#include "random.h"

#include <stdlib.h>

float randf(float min, float max) {
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

int rand_uniform(int min, int max) {
    return min + (int)((double)(max - min + 1) * rand() / (RAND_MAX + 1.0));
}