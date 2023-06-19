#ifndef LOADING_H
#define LOADING_H

#include "raylib.h"

typedef enum {
  BLINKING,
  TOP_AND_LEFT_BARS,
  BOTTOM_AND_RIGHT_BARS,
  LETTERS_APPEARING,
} LoadingState;

struct Loading {
  LoadingState state;
  int framesCounter;
  int topSideRecWidth;
  int leftSideRecHeight;
  int bottomSideRecWidth;
  int rightSideRecHeight;
  int lettersCount;
  float alpha;
  bool loaded;
};

typedef struct Loading *Loading;

extern Loading loading_create(void);

extern void update_variables(Loading test);

extern void display_loading_animation(Loading test);

#endif

