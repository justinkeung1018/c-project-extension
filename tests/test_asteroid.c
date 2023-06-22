#include "test_spaceship.h"

#include <math.h>
#include <stdlib.h>

#include "asteroid.h"
#include "list.h"
#include "raylib.h"
#include "raymath.h"
#include "test_utils.h"

void test_asteroid_move_all(void) {
  InitWindow(1920, 1080, "test");
  List as = asteroid_create_all();
  Vector2 expected_vals[as->len];

  for (int i = 0; i < as->len; i++) {
    Asteroid a = (Asteroid)list_get(as, i);
    Vector2 expected;
    expected.x = Wrap(a->position.x + a->velocity.x, 0.0 - a->size, GetScreenWidth());
    expected.y = Wrap(a->position.y + a->velocity.y, 0.0 - a->size, GetScreenHeight());
    expected_vals[i] = expected;
  }

  asteroid_move_all(as);

  Vector2 result_vals[as->len];
  for (int i = 0; i < as->len; i++) {
    result_vals[i] = ((Asteroid)list_get(as, i))->position;
  }

  assert_eq_Vector2_arr(expected_vals, result_vals, as->len, __func__);

  list_free(as);
  CloseWindow();
}

void test_asteroid_break(void) {
  InitWindow(1920, 1080, "test");
  List as = asteroid_create_all();
  int before_len = as->len;
  asteroid_break(as, 1);
  assert_eq_int(before_len + 1, as->len, __func__);
}

