#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"
#include "asteroids.h"
#include "bullet.h"
#include "spaceship.h"

void assert_eq_float(float expected, float result, int case) {
  printf("Case %d: ", case);
  if (expected == result) {
    printf("Passed.\n");
    return;
  }
  printf("Expected %lf, got %lf.\n", expected, result);
}

void assert_eq_Vector2(Vector2 expected, Vector2 result, int case) {
  printf("Case %d: ", case);
  if (expected.x == result.x && expected.y == result.y) {
    printf("Passed.\n");
    return;
  }
  printf("Expected x = %lf and y = %lf, got x = %lf and y = %lf.\n", expected.x, expected.y, result.x, result.y);
}

void test_bullet_move() {
  printf("bullet_move() tests.\n");

  for (int i = 0; i < 360; i++) {
    Bullet b = bullet_init_normal(GetScreenWidth(), GetScreenHeight(), ((float) i) / 180 * M_PI);
    
    Vector2 before = b->pos;
    Vector2 expected = (Vector2) {before.x + 25 * cos(b->rotation), before.y + 25 * sin(b->rotation)};

    bullet_move(b);

    assert_eq_Vector2(expected, before, i);
    bullet_free(b);
  }
}

void test_spaceship_rotate_right() {
  Spaceship s = spaceship_initialise();
  
  printf("spaceship_rotate_right() tests.\n");

  for (int i = 0; i < 36; i++) {
    Radians rotation_before = s->rotation;
    spaceship_rotate_right(s);
    assert_eq_float(Wrap(rotation_before + 10, 0, M_PI * 2), s->rotation, i);
  }

  spaceship_free(s);
}

void test_spaceship_rotate_left() {
  Spaceship s = spaceship_initialise();

  printf("spaceship_rotate_left() tests.\n");

  for (int i = 0; i < 36; i++) {
    Radians rotation_before = s->rotation;
    spaceship_rotate_left(s);
    assert_eq_float(Wrap(rotation_before - 10, 0, M_PI * 2), s->rotation, i);
  }

  spaceship_free(s);
}

int main (void) {
  InitWindow(1920, 1080, "Asteroids 1080p");
  
  test_bullet_move();
  test_spaceship_rotate_left();
  test_spaceship_rotate_right();

  CloseWindow();  
}