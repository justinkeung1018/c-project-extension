#include "test_spaceship.h"

#include <math.h>
#include <stdlib.h>

#include "bullet.h"
#include "list.h"
#include "raylib.h"
#include "raymath.h"
#include "test_utils.h"
#include "spaceship.h"


void test_spaceship_rotate_right() {
  Spaceship s = spaceship_initialise();

  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before + 5.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_right(s);
    assert_eq_double(expected, s->rotation, __func__);
  }

  spaceship_free(s);
}

void test_spaceship_rotate_left() {
  Spaceship s = spaceship_initialise();

  for (int i = 0; i < 36; i++) {
    Radians before = s->rotation;
    Radians expected = Wrap(before - 5.0/180.0 * M_PI, 0, M_PI * 2);
    spaceship_rotate_left(s);
    assert_eq_double(expected, s->rotation, __func__);
  }

  spaceship_free(s);
}

static void test_spaceship_accelerate_regular() {
  Spaceship s = spaceship_initialise();

  spaceship_accelerate(s);
  spaceship_accelerate(s);
  assert_eq_double(0.2, s->acceleration, __func__);

  spaceship_free(s);
}

static void test_spaceship_accelerate_max() {
  Spaceship s = spaceship_initialise();

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
  Spaceship s = spaceship_initialise();
  s->position = (Vector2){0.0, 0.0};
  spaceship_move(s);

  assert_eq_Vector2((Vector2){0.0, 0.0}, s->position, __func__);
  
  spaceship_free(s);
}

static void test_spaceship_move_accel() {
  Spaceship s = spaceship_initialise();
  s->position = (Vector2){0.0, 0.0};
  spaceship_accelerate(s);
  spaceship_move(s); 
}

void test_spaceship_move() {
  test_spaceship_move_no_accel();
}

static void test_spaceship_shoot_1_bullet() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise();

  spaceship_shoot(s, bs);

  assert_eq_int(1, bs->len, __func__);

  list_free(bs);
  spaceship_free(s);
}

static void test_spaceship_shoot_3_bullets() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise();

  spaceship_shoot(s, bs);
  spaceship_shoot(s, bs);
  spaceship_shoot(s, bs);

  assert_eq_int(3, bs->len, __func__);

  list_free(bs);
  spaceship_free(s);
}

static void test_spaceship_shoot_20_bullets() {
  List bs = bullet_init_all();
  Spaceship s = spaceship_initialise();

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