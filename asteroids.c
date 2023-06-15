#include "asteroids.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>
#include <stdlib.h>

#include "list.h"
#include "raylib.h"

#define SEED           42
#define NUM_ASTEROIDS  15

#define BASE_SIZE      30
#define VAR_SIZE       150
#define ASTEROID_SPEED 3

static Texture2D asteroid_texture;
static Rectangle asteroid_texture_rec;

static double random_num(void) {
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

void asteroids_free(List as) {
  list_free(as);
  unload_asteroid_texture();
}

List asteroids_create(void) {
  srand(SEED);
  load_asteroid_texture();
  List as = list_create(NUM_ASTEROIDS, asteroid_free);

  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    list_push(as, malloc(sizeof(struct Asteroid)));
    Asteroid a = list_get(as, i);
    assert(a != NULL);

    double angle = 2 * M_PI * random_num();
    Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
    Vector2 vel = { ASTEROID_SPEED * cos(angle), ASTEROID_SPEED * sin(angle) };
    a->size = BASE_SIZE + VAR_SIZE * random_num();
    a->position = pos;
    a->velocity = vel;
  }
  return as;
}

void asteroids_draw(List as) {
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

void asteroids_move(List as) {
  for (int i = 0; i < as->len; i++) {
    Asteroid a = list_get(as, i);
    a->position.x = Wrap(a->position.x + a->velocity.x, 0 - a->size, GetScreenWidth());
    a->position.y = Wrap(a->position.y + a->velocity.y, 0 - a->size, GetScreenHeight());
  }
}

