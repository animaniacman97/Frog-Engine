#include "engine.h"            // Engine struct + function declarations
#include <SDL3/SDL_events.h>   // SDL_Event, SDL_PollEvent, event types
#include <SDL3/SDL_init.h>     // SDL_Init, SDL_Quit
#include <SDL3/SDL_render.h>   // SDL_Renderer, create/destroy renderer
#include <SDL3/SDL_scancode.h> // Keyboard scancode constants (e.g. ESC)
#include <SDL3/SDL_video.h>    // SDL_Window, create/destroy window
#include <stdbool.h>           // bool, true, false
#include <stdio.h>             // fprintf for error logging

// Initializes SDL video, creates a window + renderer,
// and sets engine state to "running".
// Returns true on success, false on failure.
bool engine_init(struct Engine *engine, const char *title, int width,
                 int height)

{
  // Initialize SDL video subsystem.
  // If it fails, print the SDL error and abort.
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    return false;
  }

  // Create the main window
  engine->window = SDL_CreateWindow(title, width, height, 0);

  // If window creation fails, clean up SDL and abort.
  if (!engine->window) {
    fprintf(stderr, "Window error: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  // Create a renderer tied to the window.
  engine->renderer = SDL_CreateRenderer(engine->window, NULL);

  // If renderer creation fails:
  // 1) log error
  // 2) destroy window (already created)
  // 3) clear pointer
  // 4) quit SDL
  // 5) abort
  if (!engine->renderer) {
    fprintf(stderr, "Renderer error: %s\n", SDL_GetError());
    SDL_DestroyWindow(engine->window);
    engine->window = NULL;
    SDL_Quit();
    return false;
  }

  // Signal main loop to run.
  engine->is_running = true;

  return true;
}

// Cleans up renderer/window resources and shuts down SDL.
void engine_shutdown(struct Engine *engine) {
  if (engine->renderer) {
    SDL_DestroyRenderer(engine->renderer);
    engine->renderer = NULL;
  }

  // Destroy window if it exists.
  if (engine->window) {
    SDL_DestroyWindow(engine->window);
    engine->window = NULL;
  }

  // Shutdown SDL subsystems.
  SDL_Quit();
}

// Processes all pending SDL events for this frame.
void engine_events(struct Engine *engine) {
  SDL_Event event;

  // Poll events until queue is empty.
  while (SDL_PollEvent(&event)) {

    // Window close button pressed -> stop main loop.
    if (event.type == SDL_EVENT_QUIT) {
      engine->is_running = false;
    }

    // Escape key pressed -> stop main loop.
    if (event.type == SDL_EVENT_KEY_DOWN &&
        event.key.scancode == SDL_SCANCODE_ESCAPE) {
      engine->is_running = false;
    }
  }
}
