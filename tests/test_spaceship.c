#include "test_spaceship.h"

#include <math.h>
#include <stdlib.h>

#include "bullet.h"
#include "list.h"
#include "raylib.h"
#include "raymath.h"
#include "spaceship.h"
#include "test_utils.h"


void test_spaceship_rotate_right() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  double expected_vals[36];
  double result_vals[36];
  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before + 5.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_right(s);
    expected_vals[i] = expected;
    result_vals[i] = s->rotation;
  }

  assert_eq_double_arr(expected_vals, result_vals, 36, __func__);
  spaceship_free(s);
}

void test_spaceship_rotate_left() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  double expected_vals[36];
  double result_vals[36];
  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before - 5.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_left(s);
    expected_vals[i] = expected;
    result_vals[i] = s->rotation;
  }

  assert_eq_double_arr(expected_vals, result_vals, 36, __func__);
  spaceship_free(s);
}

static void test_spaceship_accelerate_regular() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  spaceship_accelerate(s);
  spaceship_accelerate(s);
  assert_eq_double(0.2, s->acceleration, __func__);

  spaceship_free(s);
}

static void test_spaceship_accelerate_max() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  spaceship_accelerate(s);
  spaceship_accelerate(s);
  spaceship_accelerate(s);
  spaceship_accelerate(s);
  assert_eq_double(0.3, s->acceleration, __func__);

  spaceship_free(s);
}

void test_spaceship_accelerate() {
  test_spaceship_accelerate_regular();
  test_spaceship_accelerate_max();
}

static void test_spaceship_move_no_accel() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);
  spaceship_move(s);

  assert_eq_Vector2((Vector2){960.0, 540.0}, s->position, __func__);
  
  spaceship_free(s);
}

static void test_spaceship_move_accel() {
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);
  spaceship_accelerate(s);
  spaceship_move(s); 

  assert_eq_Vector2((Vector2){960.0, 539.901001}, s->position, __func__);

  spaceship_free(s);
}

void test_spaceship_move() {
  InitWindow(1920, 1080, "test");
  test_spaceship_move_no_accel();
  test_spaceship_move_accel();
  CloseWindow();
}

static void test_spaceship_shoot_1_bullet() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  spaceship_shoot(s, bs);

  assert_eq_int(1, bs->len, __func__);

  list_free(bs);
  spaceship_free(s);
}

static void test_spaceship_shoot_3_bullets() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  spaceship_shoot(s, bs);
  spaceship_shoot(s, bs);
  spaceship_shoot(s, bs);

  assert_eq_int(3, bs->len, __func__);

  list_free(bs);
  spaceship_free(s);
}

static void test_spaceship_shoot_20_bullets() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise(GetScreenWidth(), GetScreenHeight(), BLACK);

  for (int i = 0; i < 20; i++) {
    spaceship_shoot(s, bs);
  }

  assert_eq_int(20, bs->len, __func__);

  list_free(bs);
  spaceship_free(s);
}

void test_spaceship_shoot() {
  test_spaceship_shoot_1_bullet();
  test_spaceship_shoot_3_bullets();
  test_spaceship_shoot_20_bullets(); 
}
