#include "loading.h"

#include <assert.h>
#include <stdlib.h>

#include "raylib.h"

// Positional constants
#define STARTING_POSITION      16
#define MAXIMUM_WIDTH          256
#define WIDTH_INCREMENT_STEP   4
#define HEIGHT_INCREMENT_STEP  4

// Title constants
#define TITLE_CHARACTER_LENGTH 9
#define LOADING_FONT_SIZE      30

// Frames constants
#define FRAMES_PER_BLINK       15
#define FRAMES_PER_LETTER      12
#define BLINKING_FRAMES_LIMIT  120

// Alpha constant
#define ALPHA_DECREMENT_STEP   0.025f

// Loading animation offsets
#define EXTRA_SMALL_OFFSET     16
#define SMALL_OFFSET           32
#define MEDIUM_OFFSET          128
#define LARGE_OFFSET           240

// Rectangle size constants
#define SMALL_REC_WIDTH        16
#define SMALL_REC_HEIGHT       16

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

      if (loader->frames_counter == BLINKING_FRAMES_LIMIT) {
        loader->state = TOP_AND_LEFT_BARS;
      }
      break;

    case TOP_AND_LEFT_BARS:
      loader->top_line_width += WIDTH_INCREMENT_STEP;
      loader->left_line_height += HEIGHT_INCREMENT_STEP;

      if (loader->top_line_width == MAXIMUM_WIDTH) {
        loader->state = BOTTOM_AND_RIGHT_BARS;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS:
      loader->bottom_line_width += WIDTH_INCREMENT_STEP;
      loader->right_line_height += HEIGHT_INCREMENT_STEP;

      if (loader->bottom_line_width == MAXIMUM_WIDTH) {
        loader->state = LETTERS_APPEARING;
      }
      break;

    case LETTERS_APPEARING:
      loader->frames_counter++;

      if (loader->frames_counter / FRAMES_PER_LETTER) {
        loader->letters_count++;
        loader->frames_counter = 0;
      }

      if (loader->letters_count > TITLE_CHARACTER_LENGTH) {
        loader->alpha -= ALPHA_DECREMENT_STEP;
        if (loader->alpha <= 0.0f) {
          loader->alpha = 0.0f;
          loader->fully_loaded = true;
        }
      }
  }
}

void display_loading_animation(Loader loader) {
  int half_width = GetScreenWidth() / 2 - MEDIUM_OFFSET;
  int half_height = GetScreenHeight() / 2 - MEDIUM_OFFSET;
  int title_string_width = MeasureText("asteroids", LOADING_FONT_SIZE);

  switch (loader->state) {
    case BLINKING:
      if ((loader->frames_counter / FRAMES_PER_BLINK) % 2) {
        DrawRectangle(half_width, half_height, SMALL_REC_WIDTH, SMALL_REC_HEIGHT, WHITE);
      }
      break;

    case TOP_AND_LEFT_BARS:
      DrawRectangle(half_width, half_height, loader->top_line_width, SMALL_REC_HEIGHT, WHITE);
      DrawRectangle(half_width, half_height, SMALL_REC_WIDTH, loader->left_line_height, WHITE);
      break;

    case BOTTOM_AND_RIGHT_BARS:
      DrawRectangle(half_width, half_height, loader->top_line_width, SMALL_REC_HEIGHT, WHITE);
      DrawRectangle(half_width, half_height, SMALL_REC_WIDTH, loader->left_line_height, WHITE);
      DrawRectangle(half_width + LARGE_OFFSET, half_height, SMALL_REC_WIDTH, loader->right_line_height, WHITE);
      DrawRectangle(half_width, half_height + LARGE_OFFSET, loader->bottom_line_width, SMALL_REC_HEIGHT, WHITE);
      break;

    case LETTERS_APPEARING:
      DrawRectangle(
          half_width,
          half_height,
          loader->top_line_width,
          SMALL_REC_HEIGHT,
          Fade(WHITE, loader->alpha));
      DrawRectangle(
          half_width,
          half_height + EXTRA_SMALL_OFFSET,
          SMALL_REC_WIDTH,
          loader->left_line_height - SMALL_OFFSET,
          Fade(WHITE, loader->alpha)
        );
      DrawRectangle(
          half_width + LARGE_OFFSET,
          half_height + EXTRA_SMALL_OFFSET,
          SMALL_REC_WIDTH,
          loader->right_line_height - SMALL_OFFSET,
          Fade(WHITE, loader->alpha)
        );
      DrawRectangle(
          half_width,
          half_height + LARGE_OFFSET,
          loader->bottom_line_width,
          SMALL_REC_HEIGHT,
          Fade(WHITE, loader->alpha)
        );
      DrawText(
          TextSubtext("asteroids", 0, loader->letters_count),
          GetScreenWidth() / 2 - title_string_width / 2,
          GetScreenHeight() / 2 - LOADING_FONT_SIZE / 2,
          LOADING_FONT_SIZE,
          Fade(WHITE, loader->alpha)
        );
  }
}

void loader_free(Loader loader) {
  free(loader);
}

