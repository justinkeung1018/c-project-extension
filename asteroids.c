#include "asteroids.h"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define SEED 42

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

asteroid *create_asteroids(int n) {
  srand(SEED);
  load_asteroid_texture();
  asteroid *as = malloc((n + 1) * sizeof(struct asteroid));
  for (int i = 0; i < n; i++) {
    as[i] = malloc(sizeof(struct asteroid));
    assert(as[i] != NULL);
    Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
    init_asteroid(as[i], 30 + 150 * random_num(), pos, 3, M_PI * random_num());
  }
  as[n] = NULL;
  return as;
}

static void free_asteroid(asteroid a) {
  free(a);
}

void free_asteroids(asteroid *as) {
  for (int i = 0; as[i] != NULL; i++){
    free_asteroid(as[i]);
  }
  free(as);
}

void draw_asteroids(asteroid *as) {
  for (int i = 0; as[i] != NULL; i++) {
    DrawTexturePro(asteroid_texture, asteroid_rec, (Rectangle){ as[i]->position.x, as[i]->position.y, as[i]->size, as[i]->size }, (Vector2){0.0f, 0.0f}, 0.0f, RAYWHITE);
  }
}

void move_asteroids(asteroid *as) {
  for (int i = 0; as[i] != NULL; i++) {
    as[i]->position.x += as[i]->speed  * cos(as[i]->rotation);
    if (as[i]->position.x < 0 || as[i]->position.x > GetScreenWidth()) {
      as[i]->position.x = GetScreenWidth() - as[i]->position.x;
    }

    as[i]->position.y += as[i]->speed * sin(as[i]->rotation);
    if (as[i]->position.y < 0 || as[i]->position.y > GetScreenHeight()) {
      as[i]->position.y = GetScreenHeight() - as[i]->position.y;
    }

  }
}

