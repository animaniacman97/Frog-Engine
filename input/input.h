#ifndef INPUT_H
#define INPUT_H

struct InputMove {
  float x;
  float y;
};

struct InputMove input_get_move(void);

#endif
