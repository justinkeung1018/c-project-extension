#include "test_collision.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "asteroids.h"
#include "collision.h"
#include "spaceship.h"
#include "raylib.h"
#include "utils.h"

#define WIDTH 60

typedef void (*TestFunc)(Asteroid, Spaceship);

static char *boolstr(bool expr) {
  return expr ? "true" : "false";
}

static void assert_true(bool expr, const char *testname) {
  if (expr) {
    printf("%-*s: OK\n", WIDTH, testname);
  } else {
    printf("%-*s: expected %s, actual %s\n", WIDTH, testname, boolstr(!expr), boolstr(expr));
  }
}

static void assert_false(bool expr, const char *testname) {
  assert_true(!expr, testname);
}

// Tip of spaceship coincides with the centre of the asteroid
// and the other two corners of the spaceship lie outside the asteroid
static void test_collides_asteroid_spaceship_centre(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 100, 100 },
    (Vector2){ 50, 50 },
    (Vector2){ 150, 50 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_intersect(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 50, 25 },
    (Vector2){ 25, 100 },
    (Vector2){ 125, 100 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_no_intersect(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 1, 1 },
    (Vector2){ 0, 0 },
    (Vector2){ 2, 0 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_false(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_tip(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 100, 50 },
    (Vector2){ 25, 25 },
    (Vector2){ 75, 25 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_left(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 75, 25 },
    (Vector2){ 100, 50 },
    (Vector2){ 25, 25 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_right(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 25, 25 },
    (Vector2){ 75, 25 },
    (Vector2){ 100, 50 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_touch(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 75, 50 },
    (Vector2){ 125, 50 },
    (Vector2){ 100, 25 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

// Spaceship entirely within asteroid
static void test_collides_asteroid_spaceship_within_asteroid(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 200, 200 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 200, 250 },
    (Vector2){ 175, 225 },
    (Vector2){ 225, 175 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

// Spaceship entirely surrounds asteroid, i.e. asteroid entirely within spaceship
static void test_collides_asteroid_spaceship_surrounds_asteroid(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 500, 500 };
  a->size = 10;

  Vector2 vectors[] = {
    (Vector2){ 500, 1000 },
    (Vector2){ 0, 0 },
    (Vector2){ 1000, 0 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

void test_collides_asteroid_spaceship(void) {
  static TestFunc tests[] = {
    test_collides_asteroid_spaceship_centre,
    test_collides_asteroid_spaceship_intersect,
    test_collides_asteroid_spaceship_no_intersect,
    test_collides_asteroid_spaceship_coincide_tip,
    test_collides_asteroid_spaceship_coincide_left,
    test_collides_asteroid_spaceship_coincide_right,
    test_collides_asteroid_spaceship_touch,
    test_collides_asteroid_spaceship_within_asteroid,
    test_collides_asteroid_spaceship_surrounds_asteroid,
  };

  for (int i = 0; i < NUM_ELEMENTS(tests); i++) {
    Asteroid a = malloc(sizeof(struct Asteroid));
    Spaceship s = malloc(sizeof(struct Spaceship));

    tests[i](a, s);

    free(a);
    free(s);
  }
}

void test_collides_asteroid_bullet(void) {

}

