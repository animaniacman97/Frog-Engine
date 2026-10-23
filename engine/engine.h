#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>

struct Engine {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool is_running;
};

bool engine_init(struct Engine *engine, const char *title, int width,
                 int height);

void engine_shutdown(struct Engine *engine);

void engine_events(struct Engine *engine);

#endif
