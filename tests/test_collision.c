#include "test_collision.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "raylib.h"
#include "spaceship.h"
#include "test_utils.h"
#include "utils.h"

typedef void (*TestAsteroidSpaceshipFunc)(Asteroid, Spaceship);
typedef void (*TestAsteroidBulletFunc)(Asteroid, Bullet);

// Tip of spaceship coincides with the centre of the asteroid
// and the other two corners of the spaceship lie outside the asteroid
static void test_collides_asteroid_spaceship_centre(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 100, 100 },
    (Vector2){ 50, 50 },
    (Vector2){ 150, 50 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_intersect_1(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 50, 25 },
    (Vector2){ 25, 100 },
    (Vector2){ 125, 100 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_intersect_2(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 80, 45 },
    (Vector2){ 45, 100 },
    (Vector2){ 0, 0 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_no_intersect_1(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 1, 1 },
    (Vector2){ 0, 0 },
    (Vector2){ 2, 0 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_false(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_no_intersect_2(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 3055, 1259 };
  a->size = 256;

  s = spaceship_initialise();

  assert_false(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_no_intersect_3(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 3558.712891, 824.832153 };
  a->size = 256;

  s = spaceship_initialise();
  s->position = (Vector2){ 1920, 1080 };

  assert_false(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_tip(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 100, 50 },
    (Vector2){ 25, 25 },
    (Vector2){ 75, 25 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_left(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 75, 25 },
    (Vector2){ 100, 50 },
    (Vector2){ 25, 25 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_coincide_right(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  Vector2 vectors[] = {
    (Vector2){ 25, 25 },
    (Vector2){ 75, 25 },
    (Vector2){ 100, 50 },
  };
  s->collider = (Collider){ vectors, NUM_ELEMENTS(vectors) };

  assert_true(collides_asteroid_spaceship(a, s), __func__);
}

static void test_collides_asteroid_spaceship_touch(Asteroid a, Spaceship s) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

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
  a->position = (Vector2){ 100, 100 };
  a->size = 200;

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
  static TestAsteroidSpaceshipFunc tests[] = {
    test_collides_asteroid_spaceship_centre,
    test_collides_asteroid_spaceship_intersect_1,
    test_collides_asteroid_spaceship_intersect_2,
    test_collides_asteroid_spaceship_no_intersect_1,
    test_collides_asteroid_spaceship_no_intersect_2,
    test_collides_asteroid_spaceship_no_intersect_3,
    test_collides_asteroid_spaceship_coincide_tip,
    test_collides_asteroid_spaceship_coincide_left,
    test_collides_asteroid_spaceship_coincide_right,
    test_collides_asteroid_spaceship_touch,
    test_collides_asteroid_spaceship_within_asteroid,
    test_collides_asteroid_spaceship_surrounds_asteroid,
  };

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(3840, 2160, __func__);

  for (int i = 0; i < NUM_ELEMENTS(tests); i++) {
    Asteroid a = malloc(sizeof(struct Asteroid));
    Spaceship s = malloc(sizeof(struct Spaceship));

    tests[i](a, s);

    free(a);
    free(s);
  }

  CloseWindow();
}

static void test_collides_asteroid_bullet_inside(Asteroid a, Bullet b) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  b->position = (Vector2){ 100, 100 };

  assert_true(collides_asteroid_bullet(a, b), __func__);
}

static void test_collides_asteroid_bullet_outside(Asteroid a, Bullet b) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  b->position = (Vector2){ 200, 200 };

  assert_false(collides_asteroid_bullet(a, b), __func__);
}

static void test_collides_asteroid_bullet_on(Asteroid a, Bullet b) {
  a->position = (Vector2){ 50, 50 };
  a->size = 100;

  b->position = (Vector2){ 50, 100 };

  assert_true(collides_asteroid_bullet(a, b), __func__);
}

void test_collides_asteroid_bullet() {
  static TestAsteroidBulletFunc tests[] = {
    test_collides_asteroid_bullet_inside,
    test_collides_asteroid_bullet_outside,
    test_collides_asteroid_bullet_on,
  };

  for (int i = 0; i < NUM_ELEMENTS(tests); i++) {
    Asteroid a = malloc(sizeof(struct Asteroid));
    Bullet b = malloc(sizeof(struct Bullet));

    tests[i](a, b);

    free(a);
    free(b);
  }
}

