#include "engine/engine.h"

int main(void) {
  struct Engine engine = {0};

  if (!engine_init(&engine, "Frog Engine", 800, 600)) {
    return 1;
  }

  while (engine.is_running) {
    engine_events(&engine);

    SDL_SetRenderDrawColor(engine.renderer, 30, 30, 30, 255);

    SDL_RenderClear(engine.renderer);
    SDL_RenderPresent(engine.renderer);

    SDL_Delay(16);
  }

  engine_shutdown(&engine);

  return 0;
}
