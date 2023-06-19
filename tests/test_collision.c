#include "test_collision.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "asteroids.h"
#include "collision.h"
#include "spaceship.h"
#include "raylib.h"

static void assert_true(bool expr, char *testname) {
  if (expr) {
    printf("%s: OK\n", testname);
  } else {
    printf("%s: expected %s, actual %s\n", testname, expr ? "false" : "true", expr ? "true" : "false");
  }
}

/*
static void assert_false(bool expr, char *testname) {
  assert_true(!expr, testname);
}
*/

static void test_collides_asteroid_spaceship_centre(void) {
  Asteroid a = malloc(sizeof(struct Asteroid));
  Spaceship s = malloc(sizeof(struct Spaceship));

  a->position = (Vector2){ 100, 100 };
  a->size = 50;

  Vector2 vectors[] = {
    (Vector2){ 100, 100 },
    (Vector2){ 50, 50 },
    (Vector2){ 150, 50 },
  };
  s->collider = (Collider){ vectors, 3 };

  assert_true(collides_asteroid_spaceship(a, s), "Test collides asteroid spaceship centre");

  free(a);
  free(s);
}


void test_collides_asteroid_spaceship(void) {
  test_collides_asteroid_spaceship_centre();
}

void test_collides_asteroid_bullet(void) {

}

