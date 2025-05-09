#ifndef STACK_VEC2_H
#define STACK_VEC2_H

#include "vector.h"

typedef struct StackVec2 StackVec2;

int get_stack_ptr(StackVec2 *stack);

Vec2 stack_pop(StackVec2 *stack);

void stack_push(StackVec2 *stack, Vec2 vec);

StackVec2 *stack_create(int capacity);

void stack_delete(StackVec2 *stack);

#endif