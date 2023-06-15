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
  Bullet *c = bullet_init(SCREEN_WIDTH, SCREEN_HEIGHT, 5, 5, 30, GREEN);
  Bullet *d = bullet_init(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, 5, 90, YELLOW);
  Bullet *e = bullet_init(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, 5, 270, BLUE);


  while (!WindowShouldClose()) {
    // update game state
    ClearBackground(RAYWHITE);
    bullet_draw(b);
    bullet_move(b);
    bullet_draw(c);
    bullet_move(c);
    bullet_draw(d);
    bullet_move(d);
    bullet_draw(e);
    bullet_move(e);
  }

  // free memory
  bullet_free(b);

  CloseWindow();

  return 0;
}

