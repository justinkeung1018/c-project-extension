#include "spaceship.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"
#include "list.h"
#include "raylib.h"
#include "raymath.h"

#define SPACESHIP_HEIGHT   200
#define SPACESHIP_WIDTH    100
#define COEFF_FRICTION     0.01

#define ACCELERATION_STEP  0.1
#define ROTATION_STEP      10

#define MIN_SPEED          0
#define MAX_SPEED          10
#define MIN_ACCELERATION   0
#define MAX_ACCELERATION   0.3
#define MIN_ROTATION       0
#define MAX_ROTATION       (2 * M_PI)

// Macros
#define RADIANS(x) (x * M_PI / 180)

Spaceship spaceship_initialise(void) {
  Spaceship s = malloc(sizeof(struct Spaceship));
  if (s == NULL) {
    fprintf(stderr, "Memory allocation for spaceship failed.\n");
    exit(EXIT_FAILURE);
  }

  s->position = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };
  s->velocity = (Vector2){ 0, 0 };
  s->acceleration = 0.0;
  s->rotation = 0.0;
  s->color = RED;

  return s;
}

void spaceship_free(Spaceship s) {
  free(s);
}

void spaceship_move(Spaceship s) {
  Vector2 acceleration_vector = (Vector2){ s->acceleration * sin(s->rotation), -(s->acceleration * cos(s->rotation)) };
  s->velocity = Vector2Add(s->velocity, acceleration_vector);
  s->velocity = Vector2ClampValue(s->velocity, MIN_SPEED, MAX_SPEED);

  Vector2 friction = (Vector2){ -s->velocity.x * COEFF_FRICTION, -s->velocity.y * COEFF_FRICTION };
  s->velocity = Vector2Add(s->velocity, friction);

  s->position.x = Clamp(s->position.x + s->velocity.x, 0, GetScreenWidth());
  s->position.y = Clamp(s->position.y + s->velocity.y, 0, GetScreenHeight());
}

void spaceship_draw(Spaceship s) {
  Vector2 top = Vector2Rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, s->rotation);
  Vector2 left = Vector2Rotate((Vector2){ -SPACESHIP_WIDTH / 2, 0 }, s->rotation);
  Vector2 right = Vector2Rotate((Vector2){ SPACESHIP_WIDTH / 2, 0 }, s->rotation);

  DrawTriangle(
      Vector2Add(s->position, top),
      Vector2Add(s->position, left),
      Vector2Add(s->position, right),
      s->color
    );
}

void spaceship_accelerate(Spaceship s) {
  s->acceleration += ACCELERATION_STEP;
  s->acceleration = Clamp(s->acceleration, MIN_ACCELERATION, MAX_ACCELERATION);
}

void spaceship_reset_acceleration(Spaceship s) {
  s->acceleration = 0;
}

void spaceship_rotate_left(Spaceship s) {
  s->rotation -= RADIANS(ROTATION_STEP);
  s->rotation = Wrap(s->rotation, MIN_ROTATION, MAX_ROTATION);
}

void spaceship_rotate_right(Spaceship s) {
  s->rotation += RADIANS(ROTATION_STEP);
  s->rotation = Wrap(s->rotation, MIN_ROTATION, MAX_ROTATION);
}

void spaceship_shoot(Spaceship s, List bs) {
  Vector2 tip = Vector2Add(s->position, Vector2Rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, s->rotation));
  list_push(bs, bullet_init(tip.x, tip.y, s->rotation - M_PI_2));
}

