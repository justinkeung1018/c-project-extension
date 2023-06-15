#include "raylib.h"
#include "asteroids.h"
#include "dynarr.h"
#include <stdlib.h>

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {

  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();

  SetTargetFPS(FPS);

  // initialise variables
  dynarr as = create_asteroids();

  while (!WindowShouldClose()) {
    // update game state
    BeginDrawing();
      ClearBackground(BLACK);
      draw_asteroids(as);
      move_asteroids(as);
    EndDrawing();
  }

  // free memory
  free_asteroids(as);

  CloseWindow();

  return 0;
}

