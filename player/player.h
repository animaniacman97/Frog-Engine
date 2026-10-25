#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL_render.h>

struct Player {
  float x;
  float y;
  float w;
  float h;
  float speed; // pixels per second
};

void player_init(struct Player *p, float x, float y, float w, float h,
                 float speed);

/* Takes raw directional intent in range [-1, 1] per axis and applies
normalized movement */
void player_update(struct Player *p, float move_x, float move_y, float dt);

// Clamps player to renderer output bounds
void player_clamp_to_renderer(struct Player *p, SDL_Renderer *renderer);

// Draws the player as a filled rectangle (temporary)
void player_render(SDL_Renderer *renderer, const struct Player *p);

#endif
