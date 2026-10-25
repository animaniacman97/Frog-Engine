#include "input.h"
#include <SDL3/SDL_keyboard.h>

struct InputMove input_get_move(void) {
  struct InputMove move = {0.0f, 0.0f};

  const bool *keys = SDL_GetKeyboardState(NULL);

  if (keys[SDL_SCANCODE_A])
    move.x -= 1.0f;
  if (keys[SDL_SCANCODE_D])
    move.x += 1.0f;
  if (keys[SDL_SCANCODE_W])
    move.y -= 1.0f;
  if (keys[SDL_SCANCODE_S])
    move.y += 1.0f;

  return move;
}
