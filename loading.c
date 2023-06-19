#include "raylib.h"
#include "loading.h"
#include <stdlib.h>
#include <assert.h>

Loader loading_initialise(void) {
  Loader loader = malloc(sizeof(struct Loader));
  assert(loader != NULL);

  loader->state = 0;
  loader->frames_counter = 0;
  loader->top_line_width = 16;
  loader->left_line_height = 16;
  loader->bottom_line_width = 16;
  loader->right_line_height = 16;
  loader->letters_count = 0;
  loader->alpha = 1.0f;
  loader->fully_loaded = false;

  return loader;
}
void update_variables(Loader loader) {
  switch (loader->state) {
    case BLINKING: // State 0: Small box blinking
      (loader->frames_counter)++;

      if (loader->frames_counter == 120) {
        loader->state = 1;
      }
      break;

    case TOP_AND_LEFT_BARS: // State 1: Top and left bars growing
      loader->top_line_width += 4;
      loader->left_line_height += 4;

      if (loader->top_line_width == 256) {
        loader->state = 2;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS: // State 2: Bottom and right bars growing
      loader->bottom_line_width += 4;
      loader->right_line_height += 4;

      if (loader->bottom_line_width == 256) {
        loader->state = 3;
      }
      break;

    case LETTERS_APPEARING: // State 3: Letters appearing (one by one)
      loader->frames_counter++;

      if (loader->frames_counter/12) {       // Every 12 frames, one more letter!
        loader->letters_count++;
        loader->frames_counter = 0;
      }

      if (loader->letters_count > 9) {     // When all letters have appeared, just fade out everything
        loader->alpha -= 0.02f;

        if (loader->alpha <= 0.0f) {
          loader->alpha = 0.0f;
          loader->fully_loaded = true;
        }
      }

  }
}

void display_loading_animation(Loader loader) {
  int half_width = GetScreenWidth()/2 - 128;
  int half_height = GetScreenHeight()/2 - 128;
  int string_length = MeasureText("asteroids", 30);

  switch (loader->state){
    case BLINKING:
      if ((loader->frames_counter / 15) % 2) {
        DrawRectangle(half_width, half_height, 16, 16, WHITE);
      }
      break;

    case TOP_AND_LEFT_BARS:
      DrawRectangle(half_width, half_height, loader->top_line_width, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, loader->left_line_height, WHITE);
      break;

    case BOTTOM_AND_RIGHT_BARS:
      DrawRectangle(half_width, half_height, loader->top_line_width, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, loader->left_line_height, WHITE);
      DrawRectangle(half_width + 240, half_height, 16, loader->right_line_height, WHITE);
      DrawRectangle(half_width, half_height + 240, loader->bottom_line_width, 16, WHITE);
      break;

    case LETTERS_APPEARING:
      DrawRectangle(half_width, half_height, loader->top_line_width, 16, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width, half_height + 16, 16, loader->left_line_height - 32, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width + 240, half_height + 16, 16, loader->right_line_height - 32, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width, half_height + 240, loader->bottom_line_width, 16, Fade(WHITE, loader->alpha));
      DrawText(TextSubtext("asteroids", 0, loader->letters_count), GetScreenWidth()/2 - string_length/2, GetScreenHeight()/2 - 15, 30, Fade(WHITE, loader->alpha));
  }
}

void loader_free(Loader loader) {
  free(loader);
}

