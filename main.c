#include "raylib.h"
#include "asteroids.h"
#include <stdlib.h>

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

#define NUM_ASTEROIDS 10

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  ToggleFullscreen();

  SetTargetFPS(FPS);

  // initialise variables
  asteroid *as = create_asteroids(NUM_ASTEROIDS);

  while (!WindowShouldClose()) {
    // update game state
    draw_asteroids(as);
    move_asteroids(as);
  }

  // free memory
  free_asteroids(as);

  CloseWindow();

  return 0;
}

