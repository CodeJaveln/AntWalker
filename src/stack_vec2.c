#include "stack_vec2.h"

#include <stdio.h>
#include <stdlib.h>

struct StackVec2 {
    int stack_ptr;
    size_t size;
    Vec2 *vec_arr;
};

int get_stack_ptr(StackVec2 *stack) {
    if (stack == NULL || stack->vec_arr == NULL) {
        fprintf(stderr, "[WARNING]: Passed invalid stack to get_stack_ptr.");
        stack_delete(stack);
        return -1;
    }

    return stack->stack_ptr;
}

Vec2 stack_pop(StackVec2 *stack) {
    if (stack == NULL || stack->vec_arr == NULL) {
        fprintf(stderr, "[WARNING]: Passed invalid stack to stack_pop.");
        stack_delete(stack);
        Vec2 vec;
        vec.x = 0;
        vec.y = 0;
        return vec;
    }

    Vec2 vec = stack->vec_arr[stack->stack_ptr];
    stack->stack_ptr--;

    return vec;
}


void stack_push(StackVec2 *stack, Vec2 vec) {
    if (stack == NULL || stack->vec_arr == NULL) {
        fprintf(stderr, "[WARNING]: Passed invalid stack to stack_push.");
        stack_delete(stack);
        return;
    }
    
    stack->stack_ptr++;
    if (stack->stack_ptr >= stack->size) { 
        stack->size = stack->stack_ptr + 2;

        stack->vec_arr = realloc(stack->vec_arr, stack->size * sizeof(Vec2));
        if (stack->vec_arr == NULL) {
            fprintf(stderr, "[ERROR]: Null ptr when reallocating the stack to fit more Vec2 in stack_push.");
            stack_delete(stack);
            return;
        }
    }

    stack->vec_arr[stack->stack_ptr] = vec;
}

StackVec2 *stack_create(int capacity) {
    if (capacity < 0) {
        fprintf(stderr, "[WARNING]: Passed invalid capacity to stack_create.");
        return NULL;
    }

    int stack_ptr = 0;
    size_t size = capacity;
    Vec2 *vec_arr = malloc(size * sizeof(Vec2));
    if (vec_arr == NULL) {
        return NULL;
    }

    StackVec2 *stack = malloc(sizeof(StackVec2));
    if (stack == NULL) {
        free(vec_arr);
        return NULL;
    }
    stack->stack_ptr = stack_ptr;
    stack->size = size;
    stack->vec_arr = vec_arr;

    return stack;
}

void stack_delete(StackVec2 *stack) {
    if (stack == NULL) {
        return;
    }

    free(stack->vec_arr);
    free(stack);
}