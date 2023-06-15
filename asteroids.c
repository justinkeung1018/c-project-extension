#include "asteroids.h"
#include "dynarr.h"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define SEED 42
#define NUM_ASTEROIDS 10

static Texture2D asteroid_texture;
static Rectangle asteroid_rec;

static double random_num(void) {
  return ((double)rand()) / RAND_MAX;
}

void load_asteroid_texture(void) {
  asteroid_texture = LoadTexture("asteroid.png");
  asteroid_rec = (Rectangle){0.0f, 0.0f, asteroid_texture.width, asteroid_texture.height};
}

void unload_asteroid_texture(void) {
  UnloadTexture(asteroid_texture);
}

static void init_asteroid(asteroid a, double size, Vector2 position, double speed, double rotation) {
  a->size = size;
  a->position = position;
  a->speed = speed;
  a->rotation = rotation;
}

static void free_asteroid(void *a) {
  free((asteroid)a);
}

void free_asteroids(dynarr as) {
  dynarr_free(as);
}

dynarr create_asteroids(void) {
  srand(SEED);
  load_asteroid_texture();
  dynarr as = dynarr_create(NUM_ASTEROIDS, free_asteroid);
  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    dynarr_push(as, malloc(sizeof(struct asteroid)));
    assert(((asteroid)dynarr_get(as, i)) != NULL);
    Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
    init_asteroid(((asteroid)dynarr_get(as, i)), 30 + 150 * random_num(), pos, 3, M_PI * random_num());
  }
  return as;
}

void draw_asteroids(dynarr as) {
  for (int i = 0; i < as->len; i++) {
    DrawTexturePro(asteroid_texture, asteroid_rec, (Rectangle){ ((asteroid)dynarr_get(as, i))->position.x, ((asteroid)dynarr_get(as, i))->position.y, ((asteroid)dynarr_get(as, i))->size, ((asteroid)dynarr_get(as, i))->size }, (Vector2){0.0f, 0.0f}, 0.0f, RAYWHITE);
  }
}

void move_asteroids(dynarr as) {
  for (int i = 0; i < as->len; i++) {
    ((asteroid)dynarr_get(as, i))->position.x += ((asteroid)dynarr_get(as, i))->speed  * cos(((asteroid)dynarr_get(as, i))->rotation);
    if (((asteroid)dynarr_get(as, i))->position.x < 0 || ((asteroid)dynarr_get(as, i))->position.x > GetScreenWidth()) {
      ((asteroid)dynarr_get(as, i))->position.x = GetScreenWidth() - ((asteroid)dynarr_get(as, i))->position.x;
    }

    ((asteroid)dynarr_get(as, i))->position.y += ((asteroid)dynarr_get(as, i))->speed * sin(((asteroid)dynarr_get(as, i))->rotation);
    if (((asteroid)dynarr_get(as, i))->position.y < 0 || ((asteroid)dynarr_get(as, i))->position.y > GetScreenHeight()) {
      ((asteroid)dynarr_get(as, i))->position.y = GetScreenHeight() - ((asteroid)dynarr_get(as, i))->position.y;
    }
  }
}

