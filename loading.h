#ifndef LOADING_H
#define LOADING_H

#include "raylib.h"

typedef enum {
  BLINKING,
  TOP_AND_LEFT_BARS,
  BOTTOM_AND_RIGHT_BARS,
  LETTERS_APPEARING,
} LoadingState;

struct Loader {
  LoadingState state;
  int frames_counter;
  int top_line_width;
  int left_line_height;
  int bottom_line_width;
  int right_line_height;
  int letters_count;
  float alpha;
  bool fully_loaded;
};

typedef struct Loader *Loader;

extern Loader loading_initialise(void);

extern void update_variables(Loader loader);

extern void display_loading_animation(Loader loader);

extern void loader_free(Loader loader);

#endif

