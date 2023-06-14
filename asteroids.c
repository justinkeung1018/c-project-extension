#include "asteroids.h"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define SEED 42

static double random_num(void) { return ((double)rand()) / RAND_MAX;
}

static void init_asteroid(asteroid a, double size, Vector2 position, double speed, double rotation) {
  a->size = size;
  a->position = position;
  a->speed = speed;
  a->rotation = rotation;
}

asteroid *create_asteroids(int n) {
  srand(SEED);
  asteroid *as = malloc((n + 1) * sizeof(struct asteroid));
  for (int i = 0; i < n; i++) {
    as[i] = malloc(sizeof(struct asteroid));
    assert(as[i] != NULL);
    Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
    init_asteroid(as[i], random_num(), pos, 3, M_PI * random_num());
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
  ClearBackground(RAYWHITE);
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
  for (int i = 0; as[i] != NULL; i++) {
    DrawCircleV(as[i]->position, 30 + 50 * as[i]->size, GRAY);
  }
}

void move_asteroids(asteroid *as) {
  for (int i = 0; as[i] != NULL; i++) {
    as[i]->position.x += as[i]->speed / (0.4 + as[i]->size) * cos(as[i]->rotation);
    if (as[i]->position.x < 0 || as[i]->position.x > GetScreenWidth()) {
      as[i]->position.x = GetScreenWidth() - as[i]->position.x;
    }

    as[i]->position.y += as[i]->speed / (0.4 +  as[i]->size) * sin(as[i]->rotation);
    if (as[i]->position.y < 0 || as[i]->position.y > GetScreenHeight()) {
      as[i]->position.y = GetScreenHeight() - as[i]->position.y;
    }

    for (int j = i + 1; as[j] != NULL; j++) {
      if (fabs(as[i]->position.x - as[j]->position.x) < 30 && fabs(as[i]->position.y - as[j]->position.y) < 30) {
        Vector2 pos = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
        init_asteroid(as[i], random_num(), pos, 3, M_PI * random_num());
        Vector2 pos2 = { GetScreenWidth() * random_num(), GetScreenHeight() * random_num() };
        init_asteroid(as[j], random_num(), pos2, 3, M_PI * random_num());
      }
    }
  }
}

