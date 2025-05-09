#ifndef HANDLE_SDL_H
#define HANDLE_SDL_H

#include <stdbool.h>
#include <SDL2/SDL.h>

bool init_sdl(SDL_Window **window, SDL_Renderer **renderer);

void quit_sdl(SDL_Window *window, SDL_Renderer *renderer);

#endif