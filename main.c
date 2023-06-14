#include "raylib.h"

#include "spaceship.h"

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();

  SetTargetFPS(FPS);

  // initialise variables
  Spaceship *spaceship = spaceship_initialise();

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsKeyDown(KEY_UP)) {
      spaceship_accelerate(spaceship);
    } else {
      spaceship_decelerate(spaceship);
    }

    if (IsKeyDown(KEY_DOWN)) {
      spaceship_decelerate(spaceship);
    }

    if (IsKeyDown(KEY_LEFT)) {
      spaceship_rotate_left(spaceship);
    }

    if (IsKeyDown(KEY_RIGHT)) {
      spaceship_rotate_right(spaceship);
    }

    spaceship_draw(spaceship);

    EndDrawing();
    // update game state
  }

  // free memory

  CloseWindow();

  return 0;
}

