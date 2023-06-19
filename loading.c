#include "raylib.h"

#include <assert.h>
#include <stdlib.h>

#include "loading.h"

#define STARTING_POSITION    16
#define MAXIMUM_WIDTH        256

#define BLINKING_FRAME_LIMIT 120

#define TITLE_CHARACTER_LENGTH 9

Loader loading_initialise(void) {
  Loader loader = malloc(sizeof(struct Loader));
  assert(loader != NULL);

  loader->state = 0;
  loader->frames_counter = 0;
  loader->top_line_width = STARTING_POSITION;
  loader->left_line_height = STARTING_POSITION;
  loader->bottom_line_width = STARTING_POSITION;
  loader->right_line_height = STARTING_POSITION;
  loader->letters_count = 0;
  loader->alpha = 1.0f;
  loader->fully_loaded = false;

  return loader;
}

void update_variables(Loader loader) {
  switch (loader->state) {
    case BLINKING:
      loader->frames_counter++;

      if (loader->frames_counter == BLINKING_FRAME_LIMIT) {
        loader->state = TOP_AND_LEFT_BARS;
      }
      break;

    case TOP_AND_LEFT_BARS:
      loader->top_line_width += 4;
      loader->left_line_height += 4;

      if (loader->top_line_width == MAXIMUM_WIDTH) {
        loader->state = BOTTOM_AND_RIGHT_BARS;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS:
      loader->bottom_line_width += 4;
      loader->right_line_height += 4;

      if (loader->bottom_line_width == MAXIMUM_WIDTH) {
        loader->state = LETTERS_APPEARING;
      }
      break;

    case LETTERS_APPEARING:
      loader->frames_counter++;

      if (loader->frames_counter / 12) {
        loader->letters_count++;
        loader->frames_counter = 0;
      }

      if (loader->letters_count > TITLE_CHARACTER_LENGTH) {
        loader->alpha -= 0.02f;

        if (loader->alpha <= 0.0f) {
          loader->alpha = 0.0f;
          loader->fully_loaded = true;
        }
      }

  }
}

void display_loading_animation(Loader loader) {
  int half_width = GetScreenWidth() / 2 - 128;
  int half_height = GetScreenHeight() / 2 - 128;
  int title_string_width = MeasureText("asteroids", 30);

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
      DrawText(TextSubtext("asteroids", 0, loader->letters_count), GetScreenWidth() / 2 - title_string_width / 2, GetScreenHeight() / 2 - 15, 30, Fade(WHITE, loader->alpha));
  }
}

void loader_free(Loader loader) {
  free(loader);
}

