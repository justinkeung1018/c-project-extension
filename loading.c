#include "raylib.h"
#include "loading.h"

void update_variables(Loading *test) {
  if (*test->state == 0) {                 // State 0: Small box blinking
    (*test->framesCounter)++;

    if (*test->framesCounter == 120) {
      *test->state = 1;
      *test->framesCounter = 0;      // Reset counter... will be used later...
    }
  }
  else if (*test->state == 1) {          // State 1: Top and left bars growing
    *test->topSideRecWidth += 4;
    *test->leftSideRecHeight += 4;

    if (*test->topSideRecWidth == 256) { 
      *test->state = 2;
    }
  }
  else if (*test->state == 2) {            // State 2: Bottom and right bars growing
    *test->bottomSideRecWidth += 4;
    *test->rightSideRecHeight += 4;

    if (*test->bottomSideRecWidth == 256) {
      *test->state = 3;
    }
  }
  else if (*test->state == 3) {            // State 3: Letters appearing (one by one)
    (*test->framesCounter)++;

    if (*test->framesCounter/12) {       // Every 12 frames, one more letter!
      (*test->lettersCount)++;
      *test->framesCounter = 0;
    }

    if (*test->lettersCount >= 10) {     // When all letters have appeared, just fade out everything
      *test->alpha -= 0.02f;

      if (*test->alpha <= 0.0f) {
        *test->alpha = 0.0f;
      }
    }
  }
}

void display_loading_animation(Loading *test) {
  if (*test->state == 0) {
    if ((*test->framesCounter/15)%2) DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, 16, BLACK);
  }
  else if (*test->state == 1) {
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, *test->topSideRecWidth, 16, BLACK);
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, *test->leftSideRecHeight, BLACK);
  }
  else if (*test->state == 2) {
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, *test->topSideRecWidth, 16, BLACK);
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, 16, *test->leftSideRecHeight, BLACK);

    DrawRectangle(GetScreenWidth()/2 - 128 + 240, GetScreenHeight()/2 - 128, 16, *test->rightSideRecHeight, BLACK);
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 240, *test->bottomSideRecWidth, 16, BLACK);
  }
  else if (*test->state == 3) {
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128, *test->topSideRecWidth, 16, Fade(BLACK, *test->alpha));
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 16, 16, *test->leftSideRecHeight - 32, Fade(BLACK, *test->alpha));

    DrawRectangle(GetScreenWidth()/2 - 128 + 240, GetScreenHeight()/2 - 128 + 16, 16, *test->rightSideRecHeight - 32, Fade(BLACK, *test->alpha));
    DrawRectangle(GetScreenWidth()/2 - 128, GetScreenHeight()/2 - 128 + 240, *test->bottomSideRecWidth, 16, Fade(BLACK, *test->alpha));

    DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, *test->alpha));

    DrawText(TextSubtext("raylib", 0, *test->lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, *test->alpha));
  }
  else if (*test->state == 4) {
    DrawText("[R] REPLAY", 340, 200, 20, GRAY);
  }
}
