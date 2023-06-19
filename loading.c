#include "raylib.h"
#include "loading.h"
#include <stdlib.h>
#include <assert.h>

Loading loading_create(void) {
  Loading a = malloc(sizeof(struct Loading));
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

void update_variables(Loading test) {

  switch (test->state) {
    case BLINKING: // State 0: Small box blinking
      (test->framesCounter)++;

      if (test->framesCounter == 120) {
        test->state = 1;
      }
      break;

    case TOP_AND_LEFT_BARS: // State 1: Top and left bars growing
      test->topSideRecWidth += 4;
      test->leftSideRecHeight += 4;

      if (test->topSideRecWidth == 256) {
        test->state = 2;
      }
      break;

    case BOTTOM_AND_RIGHT_BARS: // State 2: Bottom and right bars growing
      test->bottomSideRecWidth += 4;
      test->rightSideRecHeight += 4;

      if (test->bottomSideRecWidth == 256) {
        test->state = 3;
      }
      break;

    case LETTERS_APPEARING: // State 3: Letters appearing (one by one)
      test->framesCounter++;

      if (test->framesCounter/12) {       // Every 12 frames, one more letter!
        test->lettersCount++;
        test->framesCounter = 0;
      }

      if (test->lettersCount >= 10) {     // When all letters have appeared, just fade out everything
        test->alpha -= 0.03f;

        if (test->alpha <= 0.4f) {
          test->loaded = true;
        }
        if (test->alpha <= 0.0f) {
          test->alpha = 0.0f;
        }
      }

  }
}

void display_loading_animation(Loading test) {
  int half_width = GetScreenWidth()/2 - 128;
  int half_height = GetScreenHeight()/2 - 128;
  int string_length = MeasureText("asteroids", 30);

  switch (test->state){
    case BLINKING:
      if ((test->framesCounter / 15) % 2) {
        DrawRectangle(half_width, half_height, 16, 16, WHITE);
      }
      break;

    case TOP_AND_LEFT_BARS:
      DrawRectangle(half_width, half_height, test->topSideRecWidth, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, test->leftSideRecHeight, WHITE);
      break;

    case BOTTOM_AND_RIGHT_BARS:
      DrawRectangle(half_width, half_height, test->topSideRecWidth, 16, WHITE);
      DrawRectangle(half_width, half_height, 16, test->leftSideRecHeight, WHITE);
      DrawRectangle(half_width + 240, half_height, 16, test->rightSideRecHeight, WHITE);
      DrawRectangle(half_width, half_height + 240, test->bottomSideRecWidth, 16, WHITE);
      break;

    case LETTERS_APPEARING:
      DrawRectangle(half_width, half_height, test->topSideRecWidth, 16, Fade(WHITE, test->alpha));
      DrawRectangle(half_width, half_height + 16, 16, test->leftSideRecHeight - 32, Fade(WHITE, test->alpha));
      DrawRectangle(half_width + 240, half_height + 16, 16, test->rightSideRecHeight - 32, Fade(WHITE, test->alpha));
      DrawRectangle(half_width, half_height + 240, test->bottomSideRecWidth, 16, Fade(WHITE, test->alpha));
      // DrawText(TextSubtext("asteroids", 0, test->lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 30, Fade(WHITE, test->alpha));
      DrawText(TextSubtext("asteroids", 0, test->lettersCount), GetScreenWidth()/2 - string_length/2, GetScreenHeight()/2 - 15, 30, Fade(WHITE, test->alpha));
  }
}

