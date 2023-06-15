#include "raylib.h"
#include "bullet.h"

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

  SetTargetFPS(FPS);

  // initialise variables

  while (!WindowShouldClose()) {
    BeginDrawing();

    EndDrawing();
  }

  // free memory
  
  CloseWindow();

  return 0;
}

