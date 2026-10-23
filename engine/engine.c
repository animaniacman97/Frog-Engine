#include "engine.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

bool engine_init(struct Engine *engine, const char *title, int width,
                 int height)

{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    return false;
  }

  engine->window = SDL_CreateWindow(title, width, height, 0);

  if (!engine->window) {
    fprintf(stderr, "Window error: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  engine->renderer = SDL_CreateRenderer(engine->window, NULL);

  if (!engine->renderer) {
    fprintf(stderr, "Renderer error: %s\n", SDL_GetError());
    SDL_DestroyWindow(engine->window);
    engine->window = NULL;
    SDL_Quit();
    return false;
  }

  engine->is_running = true;

  return true;
}

void engine_shutdown(struct Engine *engine) {
  if (engine->renderer) {
    SDL_DestroyRenderer(engine->renderer);
    engine->renderer = NULL;
  }

  if (engine->window) {
    SDL_DestroyWindow(engine->window);
    engine->window = NULL;
  }

  SDL_Quit();
}

void engine_events(struct Engine *engine) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      engine->is_running = false;
    }

    if (event.type == SDL_EVENT_KEY_DOWN &&
        event.key.scancode == SDL_SCANCODE_ESCAPE) {
      engine->is_running = false;
    }
  }
}
