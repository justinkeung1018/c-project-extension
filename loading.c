#include "raylib.h"
#include "loading.h"
#include <stdlib.h>
#include <assert.h>

Loader loading_initialise(void) {
  Loader a = malloc(sizeof(struct Loader));
  assert(a != NULL);

  a->state = 0;
  a->framesCounter = 0;
  a->topSideRecWidth = 16;
  a->leftSideRecHeight = 16;
  a->bottomSideRecWidth = 16;
  a->rightSideRecHeight = 16;
  a->lettersCount = 0;
  a->alpha = 1.0f;
  a->loaded = false;

  return a;
}

void update_variables(Loader loader) {

  switch (loader->state) {
    case BLINKING: // State 0: Small box blinking
      (loader->framesCounter)++;

      if (loader->framesCounter == 120) {
        loader->state = 1;
      }
      break;

    case TOP_AND_LEFT_BARS: // State 1: Top and left bars growing
      loader->topSideRecWidth += 4;
      loader->leftSideRecHeight += 4;

      if (loader->topSideRecWidth == 256) {
        loader->state = 2;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS: // State 2: Bottom and right bars growing
      loader->bottomSideRecWidth += 4;
      loader->rightSideRecHeight += 4;

      if (loader->bottomSideRecWidth == 256) {
        loader->state = 3;
      }
      break;

    case LETTERS_APPEARING: // State 3: Letters appearing (one by one)
      loader->framesCounter++;

      if (loader->framesCounter/12) {       // Every 12 frames, one more letter!
        loader->lettersCount++;
        loader->framesCounter = 0;
      }

      if (loader->lettersCount > 9) {     // When all letters have appeared, just fade out everything
        loader->alpha -= 0.03f;

        if (loader->alpha <= 0.4f) {
          loader->loaded = true;
        }
        if (loader->alpha <= 0.0f) {
          loader->alpha = 0.0f;
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
      if ((loader->framesCounter / 15) % 2) {
        DrawRectangle(half_width, half_height, 16, 16, WHITE);
      }
      break;

    case TOP_AND_LEFT_BARS:
      DrawRectangle(half_width, half_height, loader->topSideRecWidth, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, loader->leftSideRecHeight, WHITE);
      break;

    case BOTTOM_AND_RIGHT_BARS:
      DrawRectangle(half_width, half_height, loader->topSideRecWidth, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, loader->leftSideRecHeight, WHITE);
      DrawRectangle(half_width + 240, half_height, 16, loader->rightSideRecHeight, WHITE);
      DrawRectangle(half_width, half_height + 240, loader->bottomSideRecWidth, 16, WHITE);
      break;

    case LETTERS_APPEARING:
      DrawRectangle(half_width, half_height, loader->topSideRecWidth, 16, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width, half_height + 16, 16, loader->leftSideRecHeight - 32, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width + 240, half_height + 16, 16, loader->rightSideRecHeight - 32, Fade(WHITE, loader->alpha));
      DrawRectangle(half_width, half_height + 240, loader->bottomSideRecWidth, 16, Fade(WHITE, loader->alpha));
      DrawText(TextSubtext("asteroids", 0, loader->lettersCount), GetScreenWidth()/2 - string_length/2, GetScreenHeight()/2 - 15, 30, Fade(WHITE, loader->alpha));
  }
}

void loader_free(Loader loader) {
  free(loader);
}

