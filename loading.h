#ifndef LOADING_H
#define LOADING_H

#include "raylib.h"

typedef struct {
  int *state;
  int *framesCounter;
  int *topSideRecWidth;
  int *leftSideRecHeight;
  int *bottomSideRecWidth;
  int *rightSideRecHeight;
  int *lettersCount;
  float *alpha;
} Loading;

extern void update_variables(Loading *test);

extern void display_loading_animation(Loading *test);

#endif
