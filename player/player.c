#include "player.h"
#include <SDL3/SDL_render.h>
#include <math.h>

static float clampf(float v, float min, float max) {
  if (v < min)
    return min;
  if (v > max)
    return max;
  return v;
}

void player_init(struct Player *p, float x, float y, float w, float h,
                 float speed) {
  p->x = x;
  p->y = y;
  p->w = w;
  p->h = h;
  p->speed = speed;
}

void player_update(struct Player *p, float move_x, float move_y, float dt) {
  float length = sqrtf(move_x * move_x + move_y * move_y);
  if (length > 0.0f) {
    move_x /= length;
    move_y /= length;
  }

  p->x += move_x * p->speed * dt;
  p->y += move_y * p->speed * dt;
}

void player_clamp_to_renderer(struct Player *p, SDL_Renderer *renderer) {
  int render_w = 0;
  int render_h = 0;
  SDL_GetRenderOutputSize(renderer, &render_w, &render_h);

  float max_x = (float)render_w - p->w;
  float max_y = (float)render_h - p->h;

  if (max_x < 0.0f)
    max_x = 0.0f;
  if (max_y < 0.0f)
    max_y = 0.0f;

  p->x = clampf(p->x, 0.0f, max_x);
  p->y = clampf(p->y, 0.0f, max_y);
}

void player_render(SDL_Renderer *renderer, const struct Player *p) {
  SDL_FRect rect = {p->x, p->y, p->w, p->h};
  SDL_SetRenderDrawColor(renderer, 80, 200, 120, 255);
  SDL_RenderFillRect(renderer, &rect);
}
