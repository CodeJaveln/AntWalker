#include "math_helper.h"

int math_min(int a, int b) {
    return a < b ? a : b;
}

int math_max(int a, int b) {
    return a > b ? a : b;
}

float math_minf(float a, float b) {
    return a < b ? a : b;
}

float math_maxf(float a, float b) {
    return a > b ? a : b;
}

int math_clamp(int val, int min, int max) {
    return math_max(math_min(val, max), min);
}

float math_clampf(float val, float min, float max) {
    return math_maxf(math_minf(val, max), min);
}