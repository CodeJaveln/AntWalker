#include "program.h"

#include <time.h>
#include "random.h"
#include "color.h"
#include "handle_sdl.h"

bool init_program(GameState *gameState) {
    srand(time(NULL));

    if (!init_sdl(gameState)) {
        return false;
    }
    
    gameState->color_array = calloc(gameState->screen_width * gameState->screen_width, sizeof(Vec4));
    if (gameState->color_array == NULL) {
        fprintf(stderr, "[ERROR]: color_array couldn't allocate memory.");
        return false;
    }
    
    gameState->stack = stack_create(gameState->screen_width * gameState->screen_height);
    if (gameState->stack == NULL) {
        fprintf(stderr, "[ERROR]: stack couldn't initialize.");
        return false;
    }

    Vec2 pos;
    pos.x = gameState->screen_width / 2;
    pos.y = gameState->screen_height / 2;
    stack_push(gameState->stack, pos);

    Vec4 prev_col = random_col();
    gameState->color_array[(int)pos.x + (int)pos.y * gameState->screen_width] = prev_col;

    return true;
}

void quit_program(GameState *gameState) {
    stack_delete(gameState->stack);
    free(gameState->color_array);
    quit_sdl(gameState);
    free(gameState);
}

void tick(GameState *gameState) {
    while (get_stack_ptr(gameState->stack) >= 0) {
        Vec2 cur_pos = stack_pop(gameState->stack);
        Vec2 moves_arr[4];
        int legal_moves = 0;
        for (int i = 0; i < 4; i++) {
            Vec2 temp_vec = vec2_add_direction(cur_pos, (Directions)i);
            if (temp_vec.x >= 0 && temp_vec.y >= 0 && temp_vec.x < gameState->screen_width && temp_vec.y < gameState->screen_height &&
                    vec4_is_empty(gameState->color_array[(int)temp_vec.x + (int)temp_vec.y * gameState->screen_width])) {
                moves_arr[legal_moves] = temp_vec;
                legal_moves++;
            }
        }

        if (legal_moves > 0) {
            Vec2 new_pos = moves_arr[rand_uniform(0, legal_moves - 1)];
            stack_push(gameState->stack, cur_pos);
            stack_push(gameState->stack, new_pos);

            gameState->color_array[(int)new_pos.x + (int)new_pos.y * gameState->screen_width] = generate_col(gameState->color_array[(int)(cur_pos.x) + (int)(cur_pos.y) * gameState->screen_width]);
            break;
        }
    }
}

void render(GameState *gameState) {
    SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gameState->renderer);

    for (int y = 0; y < gameState->screen_height; y++) {
        for (int x = 0; x < gameState->screen_width; x++) {
            Vec4 vec = gameState->color_array[x + y * gameState->screen_width];
            if (vec4_is_empty(vec)) {
                continue;
            }
            SDL_Color col = vec4_to_col(vec);
            SDL_SetRenderDrawColor(gameState->renderer, col.r, col.g, col.b, col.a);
            SDL_RenderDrawPointF(gameState->renderer, x, y);
        }
    }

    SDL_RenderPresent(gameState->renderer);
}