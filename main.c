#include "raylib.h"
#include "bullet.h"
#include "asteroids.h"
#include "dynarr.h"
#include <stdlib.h>

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  //ToggleFullscreen();

  SetTargetFPS(FPS);

  // initialise variables
  //asteroid *as = create_asteroids(NUM_ASTEROIDS);
  dynarr as = create_asteroids();

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    // update game state
    draw_asteroids(as);
    move_asteroids(as);
    EndDrawing();
  }

  // free memory
  
  free_asteroids(as);

  CloseWindow();

  return 0;
}

