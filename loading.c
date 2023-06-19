#include "raylib.h"

#include <assert.h>
#include <stdlib.h>

#include "loading.h"

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
    case BLINKING:
      loader->frames_counter++;

      if (loader->frames_counter == 120) {
        loader->state = 1;
      }
      break;

    case TOP_AND_LEFT_BARS:
      loader->top_line_width += 4;
      loader->left_line_height += 4;

      if (loader->top_line_width == 256) {
        loader->state = 2;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS:
      loader->bottom_line_width += 4;
      loader->right_line_height += 4;

      if (loader->bottom_line_width == 256) {
        loader->state = 3;
      }
      break;

    case LETTERS_APPEARING:
      loader->frames_counter++;

      if (loader->frames_counter/12) {
        loader->letters_count++;
        loader->frames_counter = 0;
      }

      if (loader->letters_count > 9) {
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
  int title_string_length = MeasureText("asteroids", 30);

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
      DrawText(TextSubtext("asteroids", 0, loader->letters_count), GetScreenWidth()/2 - title_string_length/2, GetScreenHeight()/2 - 15, 30, Fade(WHITE, loader->alpha));
  }
}

void loader_free(Loader loader) {
  free(loader);
}

