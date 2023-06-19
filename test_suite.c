#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "asteroids.h"
#include "bullet.h"
#include "list.h"
#include "raymath.h"
#include "raylib.h"
#include "spaceship.h"

bool assert_eq_float(float expected, float result, int number) {
  if (expected != result) {
    printf("Case %d: expected %lf, got %lf.\n", number, expected, result);
    return false;
  }
  return true;
}

bool assert_eq_Vector2(Vector2 expected, Vector2 result, int number) {
  if (expected.x != result.x && expected.y != result.y) {
    printf("Case %d: expected x = %lf and y = %lf, got x = %lf and y = %lf.\n", number, expected.x, expected.y, result.x, result.y);
    return false;
  }
  return true;
}

void test_bullet_move() {
  printf("bullet_move() tests.\n");
  int count_failed = 0;
  for (int i = 0; i < 360; i++) {
    Radians rotation = ((float) i) / 180 * M_PI;
    Bullet b = bullet_init_normal(GetScreenWidth(), GetScreenHeight(), rotation);

    Vector2 before = {GetScreenWidth(), GetScreenHeight()};
    Vector2 expected = (Vector2) {before.x + 25 * cos(rotation), before.y + 25 * sin(rotation)};

    bullet_move(b);

    if (!assert_eq_Vector2(expected, b->pos, i)) {
      count_failed++;
    }

    bullet_free(b);
  }
  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed.\n");
  }
  printf("\n");
}

void test_bullet_move_all() {
  printf("bullet_move_all() tests.\n");
  int count_failed = 0;
  List bs = bullet_init_all();
  List expected_bs = bullet_init_all();
  for (int i = 0; i < 360; i++) {
    Bullet b = bullet_init_normal(GetScreenWidth(), GetScreenHeight(), ((float) i) / 180 * M_PI);
    Bullet expected_b = bullet_init_normal(GetScreenWidth(), GetScreenHeight(), ((float) i) / 180 * M_PI);
    list_push(bs, b);
    list_push(expected_bs, expected_b);
  }

  bullet_move_all(bs);

  for (int i = 0; i < 360; i++) {
    Bullet expected_b = (Bullet) list_get(expected_bs, i);
    Vector2 expected = (Vector2) {expected_b->pos.x + 25 * cos(expected_b->rotation), expected_b->pos.y + 25 * sin(expected_b->rotation)};
    if(!assert_eq_Vector2(expected, ((Bullet) list_get(bs, i))->pos, i)) {
      count_failed++;
    }
  }

  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed.\n");
  }
  list_free(expected_bs);
  list_free(bs);
}

void test_spaceship_rotate_right() {
  Spaceship s = spaceship_initialise();

  printf("spaceship_rotate_right() tests.\n");
  int count_failed = 0;
  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before + 10.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_right(s);
    if (!assert_eq_float(expected, s->rotation, i)) {
      count_failed++;
    }
  }

  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed.\n");
  }
  spaceship_free(s);
  printf("\n");
}

void test_spaceship_rotate_left() {
  Spaceship s = spaceship_initialise();

  printf("spaceship_rotate_left() tests.\n");
  int count_failed = 0;
  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before - 10.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_left(s);
    if (!assert_eq_float(expected, s->rotation, i)) {
      count_failed++;
    }
  }

  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed.\n");
  }

  spaceship_free(s);
  printf("\n");
}

void test_spaceship_accelerate() {
  int count_failed = 0;
  /*
  code here
  */
  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed \n");
  }
}

void test_spaceship_move() {
  int count_failed = 0;
  /*
  code here
  */
  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed \n");
  }
}

void test_spaceship_shoot() {
  int count_failed = 0;
  /*
  code here
  */
  if (count_failed != 0) {
    printf("%d tests failed.\n", count_failed);
  } else {
    printf("All tests passed \n");
  }
}

int main (void) {
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(1920, 1080, "Asteroids 1080p");

  test_bullet_move();
  test_bullet_move_all();
  test_spaceship_rotate_left();
  test_spaceship_rotate_right();

  CloseWindow();
}
