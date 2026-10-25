#include "engine/engine.h" // Engine API: init, events, shutdown + Engine struct
#include "input/input.h"
#include "player/player.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

// Program entry point.
// Returns 0 on success, non-zero on failure.
int main(void) {
  // Create engine state on the stack and zero-initialize all fields.
  // window/renderer pointers start as NULL, is_running starts false.
  struct Engine engine = {0};

  // Initialize SDL video, create window + renderer.
  // If anything fails, exit with error code 1.
  if (!engine_init(&engine, "Frog Engine", 800, 600)) {
    return 1;
  }

  // Timing: counter ticks and how many ticks happen per second.
  Uint64 last_counter = SDL_GetPerformanceCounter();
  const Uint64 frequency = SDL_GetPerformanceFrequency();

  // Player x, y, width, height, speed (pixels per second)
  struct Player player;
  player_init(&player, 100.0f, 100.0f, 32.0f, 32.0f, 200.0f);

  // Main game loop.
  // Runs until engine.is_running is set false by event handling.
  while (engine.is_running) {

    Uint64 now = SDL_GetPerformanceCounter();
    float dt = (float)(now - last_counter) / (float)frequency;
    last_counter = now;

    // Clamp so a drag/pause/breakpoint doesn't cause a huge jump. (dt infinite
    // growth)
    if (dt > 0.05f) {
      dt = 0.05f;
    }

    // Process pending SDL events (quit, keyboard, etc.).
    engine_events(&engine);

    // Update.
    struct InputMove move = input_get_move();
    player_update(&player, move.x, move.y, dt);
    player_clamp_to_renderer(&player, engine.renderer);

    // Render
    SDL_SetRenderDrawColor(engine.renderer, 30, 30, 30, 255);
    SDL_RenderClear(engine.renderer);

    player_render(engine.renderer, &player);

    // Present the rendered frame to the window.
    SDL_RenderPresent(engine.renderer);

    // Small sleep to reduce CPU usage and roughly cap frame rate.
    // (~16 ms ≈ ~60 FPS, not exact timing control)
    SDL_Delay(16);
  }

  // Cleanly release renderer, window, and SDL resources.
  engine_shutdown(&engine);

  // Successful exit.
  return 0;
}
