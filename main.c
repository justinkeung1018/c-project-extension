#include "raylib.h"
#include "bullet.h"

#define FPS           60
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

  SetTargetFPS(FPS);

  // initialise variables

  Bullet *b = bullet_init(0, 0, 5, 5, 30, RED);
  Bullet *b = bullet_init(0, 0, 5, 5, 30, RED);
  Bullet *b = bullet_init(0, 0, 5, 5, 30, RED);


  while (!WindowShouldClose()) {
    // update game state
    ClearBackground(RAYWHITE);
    bullet_draw(b);
    bullet_move(b);
  }

  // free memory
  bullet_free(b);

  CloseWindow();

  return 0;
}

