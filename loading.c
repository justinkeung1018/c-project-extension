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

  return a;
}

void update_variables(Loading test) {
  switch (test->state) {
    case 0: // State 0: Small box blinking
      (test->framesCounter)++;

      if (test->framesCounter == 120) {
        test->state = 1;
        test->framesCounter = 0;      // Reset counter... will be used later...
      }
      break;

    case 1: // State 1: Top and left bars growing
      test->topSideRecWidth += 4;
      test->leftSideRecHeight += 4;

      if (test->topSideRecWidth == 256) {
        test->state = 2;
      }
      break;

    case 2: // State 2: Bottom and right bars growing
      test->bottomSideRecWidth += 4;
      test->rightSideRecHeight += 4;

      if (test->bottomSideRecWidth == 256) {
        test->state = 3;
      }
      break;

    case 3: // State 3: Letters appearing (one by one)
      (test->framesCounter)++;

      if (test->framesCounter/12) {       // Every 12 frames, one more letter!
        (test->lettersCount)++;
        test->framesCounter = 0;
      }

      if (test->lettersCount >= 10) {     // When all letters have appeared, just fade out everything
        test->alpha -= 0.02f;

        if (test->alpha <= 0.0f) {
          test->alpha = 0.0f;
        }
      }
  }
}

void display_loading_animation(Loading test) {
  switch (test->state) {
    case 0:
      if ((test->framesCounter/15)%2) DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, 16, BLACK);
      break;

    case 1:
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, test->topSideRecWidth, 16, BLACK);
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, test->leftSideRecHeight, BLACK);
      break;

    case 2:
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, test->topSideRecWidth, 16, BLACK);
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, test->leftSideRecHeight, BLACK);
      DrawRectangle(GetScreenWidth()/2 - 128 + 240, GetScreenHeight()/2 - 128, 16, test->rightSideRecHeight, BLACK);
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 240, test->bottomSideRecWidth, 16, BLACK);
      break;

    case 3:

      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, test->topSideRecWidth, 16, Fade(BLACK, test->alpha));
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 16, 16, test->leftSideRecHeight - 32, Fade(BLACK, test->alpha));
      DrawRectangle(GetScreenWidth()/2 - 128 + 240, GetScreenHeight()/2 - 128 + 16, 16, test->rightSideRecHeight - 32, Fade(BLACK, test->alpha));
      DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 240, test->bottomSideRecWidth, 16, Fade(BLACK, test->alpha));
      DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, test->alpha));
      DrawText(TextSubtext("raylib", 0, test->lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, test->alpha));
      break;

    case 4:
      DrawText("[R] REPLAY", 340, 200, 20, GRAY);
  }
}

