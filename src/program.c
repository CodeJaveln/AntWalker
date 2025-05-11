#include "program.h"

#include <time.h>

#ifdef __linux__
    #include <linux/limits.h>
#elif defined(__MINGW32__)
    #include <limits.h>
#else
    #error "Unsupported platform"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "random.h"
#include "color.h"
#include "handle_sdl.h"
#include "globals.h"

#define COL_MOD_MIN -0.005f
#define COL_MOD_MAX 0.005f

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

static Globals *globals;

Globals *get_globals(void) {
    return globals;
}

bool init_program(void) {
    srand(time(NULL));

    globals = malloc(sizeof(Globals));
    globals->screen_width = WINDOW_WIDTH;
    globals->screen_height = WINDOW_HEIGHT;

    if (!init_sdl(&globals->window, &globals->renderer)) {
        return false;
    }
    
    globals->color_array = calloc(globals->screen_width * globals->screen_height, sizeof(Vec4));
    if (globals->color_array == NULL) {
        fprintf(stderr, "[ERROR]: color_array couldn't allocate memory.");
        return false;
    }
    
    globals->stack = stack_create(globals->screen_width * globals->screen_height);
    if (globals->stack == NULL) {
        fprintf(stderr, "[ERROR]: stack couldn't initialize.");
        return false;
    }

    Vec2 pos = { globals->screen_width / 2, globals->screen_height / 2 };
    stack_push(globals->stack, pos);

    Vec4 prev_col = random_col();
    globals->color_array[(int)pos.x + (int)pos.y * globals->screen_width] = prev_col;

    return true;
}

void quit_program(void) {
    stack_delete(globals->stack);
    free(globals->color_array);
    quit_sdl(globals->window, globals->renderer);
    free(globals);
}

void tick(void) {
    while (get_stack_ptr(globals->stack) >= 0) {
        Vec2 cur_pos = stack_pop(globals->stack);
        Vec2 moves_arr[4];
        int legal_moves = 0;
        for (int i = 0; i < 4; i++) {
            Vec2 temp_vec = vec2_add_direction(cur_pos, (Directions)i);
            if (temp_vec.x >= 0 && temp_vec.y >= 0 && temp_vec.x < globals->screen_width && temp_vec.y < globals->screen_height &&
                    vec4_is_empty(globals->color_array[(int)temp_vec.x + (int)temp_vec.y * globals->screen_width])) {
                moves_arr[legal_moves] = temp_vec;
                legal_moves++;
            }
        }

        if (legal_moves > 0) {
            Vec2 new_pos = moves_arr[rand_uniform(0, legal_moves - 1)];
            stack_push(globals->stack, cur_pos);
            stack_push(globals->stack, new_pos);

            Vec4 generated_col = generate_col(globals->color_array[(int)(cur_pos.x) + (int)(cur_pos.y) * globals->screen_width], COL_MOD_MIN, COL_MOD_MAX);
            globals->color_array[(int)new_pos.x + (int)new_pos.y * globals->screen_width] = generated_col;
            break;
        }
    }
}

static unsigned char frame = 0;

void render(void) {
    frame++;
    Vec2 draw_pos = stack_peep(globals->stack);

    SDL_Color draw_col = vec4_to_col(globals->color_array[(int)draw_pos.x + (int)draw_pos.y * globals->screen_width]);
    SDL_SetRenderDrawColor(globals->renderer, draw_col.r, draw_col.g, draw_col.b, draw_col.a);
    SDL_RenderDrawPointF(globals->renderer, draw_pos.x, draw_pos.y);

    // When frame overfows
    if (frame == 0) {
        SDL_RenderPresent(globals->renderer);
    }
}


void save_image(void) {
    #define IMAGE_PATH "image.ppm"
    
    char *exe_path = SDL_GetBasePath();
    if (!exe_path) {
        fprintf(stderr, "[WARNING]: Couldn't get base path.\n");
        quit_program();
    }
    
    char picture_path[PATH_MAX];
    snprintf(picture_path, sizeof(picture_path), "%s%s", exe_path, IMAGE_PATH);
    SDL_free(exe_path);
    
    FILE *fp = fopen(picture_path, "wb");  // "wb" for binary PPM
    if (!fp) {
        fprintf(stderr, "[WARNING]: Couldn't open file to save the image.\n");
        quit_program();
    }
    
    Globals *globals = get_globals();
    fprintf(fp, "P6\n%d %d\n255\n", globals->screen_width, globals->screen_height);
    
    for (int i = 0; i < globals->screen_width * globals->screen_height; i++) {
        fputc((unsigned char)(globals->color_array[i].r * 255), fp);
        fputc((unsigned char)(globals->color_array[i].g * 255), fp);
        fputc((unsigned char)(globals->color_array[i].b * 255), fp);
    }
    
    fclose(fp);
}

bool should_quit(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                return true;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return true;
                }
            }
        }
    }

    return false;   
}