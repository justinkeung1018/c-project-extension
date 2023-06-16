#ifndef LOADING_H
#define LOADING_H

#include "raylib.h"

typedef struct {
  int state;
  int *framesCounter;
  int topSideRecWidth;
  int leftSideRecHeight;
  int bottomSideRecWidth;
  int rightSideRecHeight;
  int lettersCount;
  float alpha;
} Loading;

extern void update_variables(int state, int framesCounter, int topSideRecWidth, int leftSideRecHeight, int bottomSideRecWidth, int rightSideRecHeight, int lettersCount, float alpha);

extern void display_loading_animation(int state, int framesCounter, int logoPositionX, int logoPositionY, int topSideRecWidth, int leftSideRecHeight, int rightSideRecHeight, int bottomSideRecWidth, float alpha, int lettersCount);

#endif