#include "raylib.h"

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

  SetTargetFPS(FPS);

  // initialise variables

  while (!WindowShouldClose()) {
    // update game state
  }

  // free memory

  CloseWindow();

  return 0;
}

