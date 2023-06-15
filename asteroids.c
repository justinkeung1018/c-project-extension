#include "asteroids.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "list.h"
#include "raylib.h"

#define SEED          42
#define NUM_ASTEROIDS 15

#define BASE_SIZE     30
#define VAR_SIZE      150
#define SPEED         3

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

    Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
    a->size = BASE_SIZE + VAR_SIZE * random_num();
    a->position = pos;
    a->speed = SPEED;
    a->rotation = 2 * M_PI * random_num();
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
    a->position.x += a->speed * cos(a->rotation);
    if (a->position.x < 0 || a->position.x > GetScreenWidth()) {
      a->position.x = GetScreenWidth() - a->position.x;
    }

    a->position.y += a->speed * sin(a->rotation);
    if (a->position.y < 0 || a->position.y > GetScreenHeight()) {
      a->position.y = GetScreenHeight() - a->position.y;
    }
  }
}

