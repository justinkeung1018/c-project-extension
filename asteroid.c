#include "asteroid.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "raylib.h"
#include "utils.h"

#define SEED               42
#define NUM_ASTEROIDS      15

#define ASTEROID_SIZE      256
#define ASTEROID_SIZE_MUL  0.5f
#define ASTEROID_SPEED     2
#define ASTEROID_SPEED_MUL 2
#define ASTEROID_LEVELS    3
#define ASTEROID_ANGLE     M_PI * 0.16f

static Texture2D asteroid_texture;
static Rectangle asteroid_texture_rec;

static double random_double(void) {
  return ((double)rand()) / RAND_MAX;
}

void load_asteroid_texture(void) {
  asteroid_texture = LoadTexture("resources/asteroid.png");
  asteroid_texture_rec = (Rectangle){ 0.0f, 0.0f, asteroid_texture.width, asteroid_texture.height };
}

void unload_asteroid_texture(void) {
  UnloadTexture(asteroid_texture);
}

static void asteroid_free(void *a) {
  free((Asteroid)a);
}

void asteroid_free_all(List as) {
  list_free(as);
  unload_asteroid_texture();
}

static Asteroid asteroid_create(void) {
  Asteroid a = malloc(sizeof(struct Asteroid));
  assert(a != NULL);

  a->size = ASTEROID_SIZE;
  double angle = 2 * M_PI * random_double();

  bool on_vertical_edge = random_double() < 0.5;
  bool side = random_double() < 0.5;

  if (on_vertical_edge) {
    a->position = (Vector2){ side ? 0 : GetScreenWidth(), GetScreenHeight() * random_double() };
  } else {
    a->position = (Vector2){ GetScreenWidth() * random_double(), side ? 0 : GetScreenHeight() };
  }

  a->velocity = (Vector2){ ASTEROID_SPEED * cos(angle), ASTEROID_SPEED * sin(angle) };

  return a;
}

List asteroid_create_all(void) {
  srand(SEED);
  load_asteroid_texture();
  List as = list_create(NUM_ASTEROIDS, asteroid_free);

  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    Asteroid a = asteroid_create();
    list_push(as, a);
  }

  return as;
}

void asteroid_draw_all(List as) {
  for (int i = 0; i < as->len; i++) {
    Asteroid a = list_get(as, i);
    Rectangle a_rec = { a->position.x, a->position.y, a->size, a->size };

    DrawTexturePro(
        asteroid_texture,
        asteroid_texture_rec,
        a_rec,
        (Vector2){ 0.0f, 0.0f },
        0.0f,
        RAYWHITE
      );
  }
}

void asteroid_move_all(List as) {
  for (int i = 0; i < as->len; i++) {
    Asteroid a = list_get(as, i);
    a->position.x = Wrap(a->position.x + a->velocity.x, 0 - a->size, GetScreenWidth());
    a->position.y = Wrap(a->position.y + a->velocity.y, 0 - a->size, GetScreenHeight());
  }
}

static Asteroid asteroid_create_child(Asteroid parent, bool left) {
  Asteroid a = asteroid_create();
  a->size = parent->size * ASTEROID_SIZE_MUL;
  a->position = parent->position;
  a->velocity = Vector2Scale(parent->velocity, ASTEROID_SPEED_MUL);
  a->velocity = Vector2Rotate(a->velocity, (left ? 1 : -1) * ASTEROID_ANGLE);
  return a;
}

void asteroid_break(List as, int idx) {
  Asteroid a = list_remove(as, idx);
  if (a->size == ASTEROID_SIZE * pow(ASTEROID_SIZE_MUL, (ASTEROID_LEVELS - 1))) {
    return;
  }
  Asteroid c1 = asteroid_create_child(a, true);
  Asteroid c2 = asteroid_create_child(a, false);
  list_push(as, c1);
  list_push(as, c2);
}

