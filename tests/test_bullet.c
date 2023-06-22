#include "test_bullet.h"

#include <math.h>

#include "bullet.h"
#include "list.h"
#include "raylib.h"
#include "test_utils.h"

void test_bullet_move() {
  Vector2 expected_vals[360];
  Vector2 result_vals[360];
  for (int i = 0; i < 360; i++) {
    Radians rotation = ((double)i) / 180 * M_PI;
    Bullet b = bullet_init(1920, 1080, rotation, BLACK);

    Vector2 before = {1920, 1080};
    Vector2 expected = (Vector2){ before.x + 25 * cos(rotation), before.y + 25 * sin(rotation) };

    bullet_move(b);

    expected_vals[i] = expected;
    result_vals[i] = b->position;

    bullet_free(b);
  }

  assert_eq_Vector2_arr(expected_vals, result_vals, 360, __func__);
}

void test_bullet_move_all() {
  List bs = bullet_init_all();
  List expected_bs = bullet_init_all();
  for (int i = 0; i < 360; i++) {
    Bullet b = bullet_init(GetScreenWidth(), GetScreenHeight(), ((double) i) / 180 * M_PI, BLACK);
    Bullet expected_b = bullet_init(GetScreenWidth(), GetScreenHeight(), ((double) i) / 180 * M_PI, BLACK);
    list_push(bs, b);
    list_push(expected_bs, expected_b);
  }

  bullet_move_all(bs);

  Vector2 expected_vals[360];
  Vector2 result_vals[360];
  for (int i = 0; i < 360; i++) {
    Bullet expected_b = (Bullet)list_get(expected_bs, i);
    Vector2 expected = (Vector2) {expected_b->position.x + expected_b->speed * cos(expected_b->rotation), expected_b->position.y + expected_b->speed * sin(expected_b->rotation)};
    expected_vals[i] = expected;
    result_vals[i] = ((Bullet) list_get(bs, i))->position;
  }

  assert_eq_Vector2_arr(expected_vals, result_vals, 360, __func__);

  list_free(expected_bs);
  list_free(bs);
}

static void test_bullet_in_screen_true() {
  Bullet b = bullet_init(1, 1, 0, BLACK);
  assert_true(bullet_in_screen(b), __func__);
  bullet_free(b);
}

static void test_bullet_in_screen_false_1() {
  Bullet b = bullet_init(1921, 1080, 0, BLACK);
  assert_false(bullet_in_screen(b) ,__func__);
  bullet_free(b);
}

static void test_bullet_in_screen_false_2() {
  Bullet b = bullet_init(1920, 1081, 0, BLACK);
  assert_false(bullet_in_screen(b) ,__func__);
  bullet_free(b);
}

static void test_bullet_in_screen_false_3() {
  Bullet b = bullet_init(1921, 1081, 0, BLACK);
  assert_false(bullet_in_screen(b) ,__func__);
  bullet_free(b);
}

static void test_bullet_in_screen_false_4() {
  Bullet b = bullet_init(-1, -1, 0, BLACK);
  assert_false(bullet_in_screen(b) ,__func__);
  bullet_free(b);
}

void test_bullet_in_screen() {
  InitWindow(1920, 1080, "test");
  test_bullet_in_screen_true();
  test_bullet_in_screen_false_1();
  test_bullet_in_screen_false_2();
  test_bullet_in_screen_false_3();
  test_bullet_in_screen_false_4();
  CloseWindow();
}

static void test_bullet_despawn_all_off_screen_1() {
  List bs = bullet_init_all();
  Bullet b = bullet_init(1921, 1081, 0, BLACK);

  list_push(bs, b);
  bullet_despawn_all_off_screen(bs);

  assert_eq_int(0, bs->len, __func__);
}

static void test_bullet_despawn_all_off_screen_5() {
  List bs = bullet_init_all();

  Bullet b1 = bullet_init(1921, 1081, 0, BLACK);
  Bullet b2 = bullet_init(1921, 1081, 0, BLACK);
  Bullet b3 = bullet_init(1921, 1081, 0, BLACK);
  Bullet b4 = bullet_init(1921, 1081, 0, BLACK);
  Bullet b5 = bullet_init(1921, 1081, 0, BLACK);

  list_push(bs, b1);
  list_push(bs, b2);
  list_push(bs, b3);
  list_push(bs, b4);
  list_push(bs, b5);

  bullet_despawn_all_off_screen(bs);

  assert_eq_int(0, bs->len, __func__);
}

void test_bullet_despawn_all_off_screen() {
  InitWindow(1920, 1080, "test");
  test_bullet_despawn_all_off_screen_1();
  test_bullet_despawn_all_off_screen_5();
  CloseWindow();
}

